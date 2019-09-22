/*********************************************************************************
** File Name    : simulator.cpp                                                      **
** Purpose      : Defines class 'Simulator' 	                                        **
** Author       : Anju K.James<anju@nmsu.edu>, Edgar Ceh Varela<eceh@nmsu.edu>  **
** Version      : 1.0                                                           **
*********************************************************************************/

/* HEADERS */

#include "simulator.h"

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

/* FUNCTIONS */

/******************************************************************************
 ** Function    : Simulator()
 ** Description : Constructor
 ** @return     : No return value.
 *****************************************************************************/
Simulator::Simulator()
{
}

/******************************************************************************
 ** Function    : getRandomBetween() 
 ** Description : Method for obtaining a random number between a range
 ** @param1     : Range start point
 ** @param2     : Range end point
 ** @return     : Returns a random number.
 *****************************************************************************/
int Simulator::getRandomBetween( int x, int y )
{
    int randomNum = rand() % ( y - x + 1 ) + x;
    return randomNum;
}

/******************************************************************************
 ** Function    : getRandomTime() 
 ** Description : Method to get the Poisson distribution for packet generation time
 ** @return     : Returns a random number.
 *****************************************************************************/
int Simulator::getRandomTime()
{
    float u = getUniformRandomVar();
    return round( ( -1/LAMBDA ) * log( u ) );

}

/******************************************************************************
 ** Function    : getUniformRandomVar()
 ** Description : Method for getting a standard uniform random variable
 **               This is for the Bandwidth and the Packt size
 ** @return     : Returns a random float value.
 *****************************************************************************/
float Simulator::getUniformRandomVar()
{
    return ( float )rand() / RAND_MAX;
}

/******************************************************************************
 ** Function    : getDelay()
 ** Description : Method to get the transmission delay
 ** @return     : Returns a random variable.
 *****************************************************************************/
int Simulator::getDelay()
{
    float u = getUniformRandomVar();
    return round( DELAY_DISTRIBUTION_START + u * ( DELAY_DISTRIBUTION_STOP - DELAY_DISTRIBUTION_START ) );
}

/******************************************************************************
 ** Function    : SetSourceNodes() 
 ** Description : Set all source nodes
 ** @param1     : Array of all nodes
 ** @param2     : Number of total nodes
 ** @param3     : Source destination pair already found
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::SetSourceNodes( Node nodes[], int node_count, src_destn_pair* pairs )
{
    for( int i = 0; i < node_count; ++i )
    {
	if( pairs->find( i ) == pairs->end() )
	{
	    continue;
	}
	else
	{
	    nodes[i].setSource();
	}
    }
}

/******************************************************************************
 ** Function    : CreatePacketInSourceNodes() 
 ** Description : Create packets in source nodes, if time to generate packet 
 **               in that node matches with current time 
 ** @param1     : Total node count
 ** @param2     : Array of all nodes
 ** @param3     : Source destination pair
 ** @param4     : Object of graph class
 ** @param5     : Current time
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::CreatePacketInSourceNodes( int node_count, Node nodes[], src_destn_pair* pairs, Graph* graph, int time )
{
    packet data;
    queue* opq;
    float rand;
    int nexthop;
    int time_to_create_new_packet;

    cout <<"\n..........Creating packets in source nodes.........." << time << endl;

    for( int i = 0; i < node_count; ++i )
    {
	if( pairs->find( i ) == pairs->end() )
	{
	    continue;
	}
	else
	{
	    // Find the destination for each source node, create packet and push to output queue.
	    for( auto index = pairs->find( i )->second.begin() ; index != pairs->find( i )->second.end() ; ++index )
	    {
		time_to_create_new_packet = nodes[ i ].GetTimeToCreatePacket();

		//create new packet only if time matches
		if( time_to_create_new_packet == time )
		{
		    opq = nodes[ i ].GetOutputQueue();
		    rand = getUniformRandomVar();
		    nodes[ i ].GeneratePacket( &data, i, *index, rand, time );
		    ++total_packets_generated;
		    nexthop = graph->GetNextHop( i,*index );

		    cout << "New packet created in source node: " << i << " -> src: " << data.source 
			<< " Dstn: " << data.destination << " size: " << data.data_size 
			<< " Time: " << data.time_of_creation << endl;

		    //if( ( vec->size() < QUEUE_SIZE ) || ( time == 1 ) )
		    if( ( opq->find( nexthop )->second.size() < QUEUE_SIZE ) || ( time == 1 ) )
		    {
			nodes[ i ].PushPacket( opq, nexthop, data );
		    }
		    else
		    {
			cout << "Queue is full ...Dropping Packet!!! queue size: " << opq->find( nexthop )->second.size() << endl;
			nodes[ i ].SetDropCount( 1 );
		    }

		    //Calculating time to create next packet
		    while( time_to_create_new_packet == time )
		    {
			nodes[ i ].SetTimeToCreatePacket( getRandomTime() + time );
			time_to_create_new_packet = nodes[ i ].GetTimeToCreatePacket();
		    }
		}
	    }
	}
    }
}

/******************************************************************************
 ** Function    : Init() 
 ** Description : Do all the operations to be done in time = 0(just before staring simulator)
 ** @param1     : Total node count
 ** @param2     : Array of all nodes
 ** @param3     : Source destination pair
 ** @param4     : Object of graph class
 ** @param5     : Current time
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::Init( int node_count, Node nodes[], src_destn_pair* pairs, Graph* graph )
{
    //Set Node ID for all nodes
    for( int i = 0; i < node_count; ++i )
    {
	nodes[ i ].setID( i );
    }

    SetSourceNodes( nodes, node_count, pairs );

    //Calculate 'time to send packet' for all source nodes for first iteration.
    for( int i=0; i <node_count; ++i )
    {
	if( nodes[ i ].getIsSource() )
	{
	    nodes[ i ].SetTimeToCreatePacket( 1 );
	    cout << "packet send time for node "<<i<<" is " << nodes[ i ].GetTimeToCreatePacket() << endl;

	} 

    }
}

/******************************************************************************
 ** Function    : ProcessOutputQueues() 
 ** Description : Processing output queues of all nodes. If channel is free,
 ** 		  move first packet from queue to channel 
 ** @param1     : Array of all nodes
 ** @param2     : Total node count
 ** @param3     : Current time
 ** @param4     : Object of graph class
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::ProcessOutputQueues( Node nodes[], int node_count, int time, Graph* graph )
{
    queue* opq = {};
    packet data = {};
    connection* channel = {}; 
    float size = 0.0;
    float bandwidth = 0.0;
    int delay = 0;
    int total_delay = 0;
    int time_to_process_channel = 0;
    packet_vector* vec = {};

    cout <<"\n..........Processing Output Queues.........." << time << endl;

    for ( int i = 0; i < node_count; ++i )
    {
	opq = nodes[ i ].GetOutputQueue();
	//nodes[ i ].PrintQueue( opq );
	channel = nodes[ i ].GetWire();	

	if( !opq->empty() )
	{
	    for( auto index = opq->begin(); index != opq->end(); ++index )
	    {
		cout << "Node :" << i << " Link: " << index->first << endl;
		if( channel->find( index->first ) == channel->end() )
		{
		    cout << "Channel is free.." << endl;
		    // Not found means, channel is free. Insert a new key value pair to channel after popping data from opq
		    data = nodes[ i ].PopPacket( opq, index->first );

		    //Calculate the total transmission delay for channel
		    size = data.data_size;
		    bandwidth = graph->GetChannelBandwidth( i, index->first );
		    delay = graph->GetChannelDelay( i, index->first );
		    total_delay = delay + ceil( size / bandwidth );
		    total_transmission_time += total_delay;
		    ++total_transmissions;
		    time_to_process_channel = total_delay + time;
		    cout << "Next time to process channel " << i << " <-> " <<index->first << " is " << time_to_process_channel << endl;

		    graph->SetChannelTotalDelay( i, index->first, time_to_process_channel );
		    nodes[ i ].SetWire( index->first, data );

		    continue;
		}
		else
		{
		    for( auto idx = channel->begin(); idx != channel->end(); ++idx )
		    {
			if( idx->first == index->first )
			{
			    if( idx->second.data_size == 0 )
			    {
				cout << "Channel is free.... Packet size: " << idx->second.data_size << " output queue to process : "<< i <<"-"<< index->first <<endl;
				vec = &index->second;
				if( !vec->empty() )
				{
				    data = nodes[ i ].PopPacket( opq, index->first );

				    //Calculate the total transmission delay for channel
				    size = data.data_size;
				    bandwidth = graph->GetChannelBandwidth( i, index->first );
				    delay = graph->GetChannelDelay( i, index->first );
				    total_delay = delay + ceil( size / bandwidth );

				    total_transmission_time += total_delay;
				    ++total_transmissions;

				    time_to_process_channel = total_delay + time;
				    cout << "Next time to process channel " << i << " <-> " <<index->first << " is " << time_to_process_channel << endl;

				    graph->SetChannelTotalDelay( i, index->first, time_to_process_channel );
				    nodes[ i ].SetWire( index->first, data );
				}
			    }
			}
		    } 
		}
	    } 
	}

	cout << "==Output Queue=="<<endl;
	nodes[ i ].PrintQueue( opq );
    }
}

/******************************************************************************
 ** Function    : ProcessInputQueues()
 ** Description : Process input queues of all nodes. if destination is reached,
 ** 		  mark as received successfully. else forward to output queue.
 ** @param1     : Array of all nodes
 ** @param2     : Total node count
 ** @param3     : Current time
 ** @param4     : Object of graph class
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::ProcessInputQueues( Node nodes[], int node_count, int time, Graph* graph )
{
    queue* ipq = {};
    queue* opq = {};
    packet data;
    int nexthop;
    packet_vector *vec = {};
    int transmission_time = 0;

    cout <<"\n..........Processing Input Queues.........." << time << endl;

    for ( int i = 0; i < node_count; ++i )
    {
	ipq = nodes[ i ].GetInputQueue();
	opq = nodes[ i ].GetOutputQueue();

	if( !ipq->empty() )
	{
	    for( auto index = ipq->begin(); index != ipq->end(); ++index )
	    {
		vec = &index->second;
		if( !vec->empty() )
		{
		    cout << "processing input queue of node: " << i << " link: " << index->first << endl;  
		    if( i == index->second[0].destination )
		    {
			cout << "Packet received successfully in destination " << index->first << " at time " << time << endl;
			cout << "Packet-> src: " << index->second[0].source << " Dstn: " << index->second[0].destination 
			    << " size: " << index->second[0].data_size << " Time: " << index->second[0].time_of_creation << endl;

			// Statistics
			++total_packets_received;
			transmission_time = time - index->second[0].time_of_creation;
			total_success_transmission_time += transmission_time;

			if( transmission_time < min_transmission_time )
			{
			    min_transmission_time = transmission_time;
			} 
			if( max_transmission_time < transmission_time )
			{
			    max_transmission_time = transmission_time;
			}

			//Delete packet from input queue since it reached in destination
			vec->erase( vec->begin(), vec->begin() + 1 );
		    }
		    else
		    {
			nexthop = graph->GetNextHop( i, index->second[0].destination );

			cout << "Forward packet from "<< i << " to " << nexthop << " packet-> src: " 
			    << index->second[0].source << " Dstn: " << index->second[0].destination 
			    << " size: " << index->second[0].data_size << " Time: " 
			    << index->second[0].time_of_creation << endl;

			if( !opq->empty() )
			{
			    if( opq->find( nexthop ) == ipq->end() )
			    {
				// Not found means, push packet to the output queue for the first time
				// Pop data from input queue and push to output queue
				data = nodes[ i ].PopPacket( ipq, index->first );
				nodes[ i ].PushPacket( opq, nexthop, data );
			    }
			    else
			    {
				if ( ( opq->find( nexthop )->second.size() < QUEUE_SIZE ) || ( opq->find( nexthop )->second.size() > 10000 ) )
				{
				    //TODO: Check y garbage value is returned for size()
				    cout<< "The input Queuses of node " << i << endl;
				    nodes[ i ].PrintQueue( ipq );
				    data = nodes[ i ].PopPacket( ipq, index->first );
				    nodes[ i ].PushPacket( opq, nexthop, data );
				}
				else
				{
				    cout << "Output queue is full...Drop the packet! 01 queue size: " << opq->find( nexthop )->second.size() << endl;
				    data = nodes[ i ].PopPacket( ipq, index->first );
				    nodes[ i ].SetDropCount( 1 );

				}
			    }
			}
			else
			{
			    data = nodes[ i ].PopPacket( ipq, index->first );
			    nodes[ i ].PushPacket( opq, nexthop, data );
			}
		    }

		    cout << "==Input Queue=="<<endl;
		    nodes[ i ].PrintQueue( ipq );

		    cout << "==Output Queue=="<<endl;
		    nodes[ i ].PrintQueue( opq );
		}
	    }
	}
    }
}

/******************************************************************************
 ** Function    : DataTransmission()
 ** Description : Handle the data transmission through wire.
 **               If delay time is over, move the packet to input queue of
 **               nexthop
 ** @param1     : Array of all nodes
 ** @param2     : Total node count
 ** @param3     : Current time 
 ** @param3     : Object of Graph class
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::DataTransmission( Node nodes[], int node_count, int time, Graph* graph )
{
    packet data;
    packet empty_packet;
    connection* channel;
    int time_to_process_wire;
    queue* ipq;
    int nexthop;
    vector<int> free_channel;

    cout <<"\n..........Data Transmission.........." << time << endl;

    for ( int i = 0; i < node_count; ++i )
    {
	//Get the map of all the channels in node i
	channel = nodes[ i ].GetWire();
	nodes[ i ].GeneratePacket( &empty_packet, 0, 0, 0.0, 0 );

	//process if there is something in wire
	if( !channel->empty() )
	{
	    //Process all channels one by one
	    for( auto index = channel->begin(); index != channel->end(); ++index )
	    {
		data = index->second;
		time_to_process_wire = graph->GetChannelTotalDelay( i, index->first );

		if( time_to_process_wire == time )
		{
		    //find the next hope to identify the input queue link of next node
		    nexthop = graph->GetNextHop( index->first, data.destination );
		    cout <<"Time to process wire matches... node: "<< i << " Link: "<< index->first << " Time: " <<time_to_process_wire <<endl;

		    //Get all the input queues of index->first
		    ipq = nodes[ index->first ].GetInputQueue();
		    if( !ipq->empty() )
		    {
			//check whether a queue exist for link 'nexthop' already in input queue list 
			if( ipq->find( nexthop ) == ipq->end() )
			{

			    // Not found means, push packet to the input queue for the first time
			    nodes[ index->first ].PushPacket( ipq, nexthop, data );
			    nodes[ i ].SetWire( index->first, empty_packet );
			    graph->SetChannelTotalDelay( i, index->first, 0 );
			}
			else
			{
			    if( ( ipq->find( nexthop )->second.size() < QUEUE_SIZE ) || ( ipq->find( nexthop )->second.size() > 10000 ) )
			    {
				nodes[ index->first ].PushPacket( ipq, nexthop, data );
				nodes[ i ].SetWire( index->first, empty_packet );
				graph->SetChannelTotalDelay( i, index->first, 0 );
			    }
			    else
			    {
				//Input queue is full.. Drop the packeti
				cout << "Drop this packet!" << endl;
				nodes[ i ].SetWire( index->first, empty_packet );
				graph->SetChannelTotalDelay( i, index->first, 0 );
				nodes[ i ].SetDropCount( 1 );
			    }
			}
		    }
		    else
		    {
			nexthop = graph->GetNextHop( index->first, data.destination );
			nodes[ index->first ].PushPacket( ipq, nexthop, data );
			cout << "4. Setting wire empty node: " << i << " Link: " << index->first << endl;
			nodes[ i ].SetWire( index->first, empty_packet );
			graph->SetChannelTotalDelay( i, index->first, 0 );
		    }

		}
		else
		{
		    //Keep data in channel till the time to process matches with current time.
		    cout << "Keep data in channel:  " << i << " <-> "<< index->first 
			<< " src: " << data.source << " dstn: " << data.destination 
			<< " size: " << data.data_size << endl;
		}
	    }

	}
    }
}

/******************************************************************************
 ** Function    : RunSimulator() 
 ** Description : Run the simulator
 ** @param1     : Array of all nodes
 ** @param2     : Total number of nodes
 ** @param3     : Object of graph
 ** @param4     : Source destination pair
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::RunSimulator( Node nodes[], int node_count, Graph* graph, src_destn_pair* pairs )
{
    for( int i = 1 ; i <= SIMULATOR_TIME; ++i )
    {
	cout << "\n====================================================" << endl;
	cout << "========================Time: " << i <<" ====================" << endl;
	cout << "====================================================\n" << endl;

	CreatePacketInSourceNodes( node_count, nodes, pairs, graph, i );
	ProcessOutputQueues( nodes, node_count, i, graph );
	DataTransmission( nodes, node_count, i, graph );
	ProcessInputQueues( nodes, node_count, i, graph );
    }
}

/******************************************************************************
 ** Function    : GenerateStatistics()
 ** Description : Method to generate statistics report
 ** @param1     : List of all nodes
 ** @param2     : Total number of nodes
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::GenerateStatistics( Node nodes[], int node_count )
{
    int packets_dropped = 0;
    float avg_transmission_time = 0.0;
    float percentage_received_packets = 0.0;
    float avg_drop_count = 0.0;
    float avg_packet_transmission_time = 0.0;

    cout << "\n\n========== STATISTICS ========== \n";
    //1.Total Number of packets generated
    cout << "1. Total Number of packets generated\t\t\t\t:\t" << total_packets_generated << endl;

    //2.Total Number of packets Reached Destination successfully
    cout << "2. Total Number of packets Reached Destination successfully\t:\t" << total_packets_received << endl;

    //3.Percentage of successfully received packets
    percentage_received_packets = ( ( float )total_packets_received * 100 ) / ( float )total_packets_generated;
    cout << "3. Percentage of successfully received packets\t\t\t:\t" << percentage_received_packets << endl;

    //4.Average packet transmission time for each transmission
    //Note: Moving one packet from one node( output queue ) to next node( input queue ) is considered as a transmission
    avg_packet_transmission_time = total_transmission_time / ( float ) total_transmissions;
    cout << "4. Average packet transmission time for each transmission\t:\t" << avg_packet_transmission_time << endl;

    //5.Maximum,Minimum and average time for completion for the transmissions
    cout << "5. Time for completion for the transmissions" << endl;
    cout << "\ta. Maximum time for completion for the transmissions\t:\t" << max_transmission_time << endl;
    cout << "\tb. Minimum time for completion for the transmissions\t:\t" << min_transmission_time << endl;
    avg_transmission_time = ( float )total_success_transmission_time / ( float )total_packets_received;
    cout << "\tc. Average time for completion for the transmissions\t:\t" << avg_transmission_time << endl;

    //6.Maximum,Minimum and average number of packets dropped at a router
    for( int i = 0; i < node_count; ++i )
    {
	packets_dropped = nodes[ i ].GetDropCount();
	total_drop_count += packets_dropped;
	if( packets_dropped < min_drop_count )
	{
	    min_drop_count = packets_dropped;
	}

	if( max_drop_count < packets_dropped )
	{
	    max_drop_count = packets_dropped;
	}

    } 
    cout << "6. Packets dropped at a router" << endl;
    cout << "\ta. Maximum number of packets dropped at a router\t:\t" << max_drop_count << endl;
    cout << "\tb. Minimum number of packets dropped at a router\t:\t" << min_drop_count << endl;
    avg_drop_count = ( ( float )total_drop_count ) / ( float )node_count;
    cout << "\tc. Average number of packets dropped at a router\t:\t" << avg_drop_count << endl;
}

/******************************************************************************
 ** Function    : InitializeSimulator() 
 ** Description : Configure Simulator 
 ** @param1     : Total node count
 ** @param2     : source destination pair
 ** @param3     : Object of graph class
 ** @return     : No return value.
 *****************************************************************************/
void Simulator::InitializeSimulator( int node_count, src_destn_pair* pairs, Graph* graph )
{
    Node nodes[node_count];

    Init( node_count, nodes, pairs, graph );
    RunSimulator( nodes, node_count, graph, pairs );
    GenerateStatistics( nodes, node_count );
}
