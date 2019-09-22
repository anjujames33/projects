/*********************************************************************************
** File Name    : node.cpp                                                      **
** Purpose      : Defines class 'Node' 	                                        **
** Author       : Edgar Ceh Varela<eceh@nmsu.edu>, Anju K.James<anju@nmsu.edu>  **
** Version      : 1.0                                                           **
*********************************************************************************/

/* HEADERS */

#include "node.h"

/* FUNCTIONS */

/******************************************************************************
 ** Function    : Node() 
 ** Description : Constructor
 ** @return     : No return value.
 *****************************************************************************/
Node::Node() : input_queue(), output_queue(), wire()
{
    this->id = -1;
    this->is_source = false;
    this->time_to_create_packet = 0;
    this->drop_count = 0;
}

/******************************************************************************
 ** Function    : setID() 
 ** Description : Method to set node id
 ** @param1     : ID of node
 ** @return     : No return value.
 *****************************************************************************/
void Node::setID(int id)
{
    this->id = id;
}


/******************************************************************************
 ** Function    : getID() 
 ** Description : Method to get the id of node
 ** @return     : Returns the id of node.
 *****************************************************************************/
int Node::getID()
{
    return this->id;
}


/******************************************************************************
 ** Function    : setSource()
 ** Description : Methos to set is_source flag, if node is a source
 ** @return     : No return value.
 *****************************************************************************/
void Node::setSource()
{
    this->is_source = true;
}

/******************************************************************************
 ** Function    : getIsSource()
 ** Description : Method to check whether the node is a source node.
 ** @return     : Returns the value of is_source flag( true or false ).
 *****************************************************************************/
bool Node::getIsSource()
{
    return is_source;
}

/******************************************************************************
 ** Function    : GetInputQueue() 
 ** Description : Method to get all input queues of a node
 ** @return     : Returns a pointer to input queues of node.
 *****************************************************************************/
queue* Node::GetInputQueue()
{
    return &this->input_queue;
}

/******************************************************************************
 ** Function    : GetOutputQueue()
 ** Description : Method to get all output queues of a node
 ** @return     : Returns a pointer to output queues of node.
 *****************************************************************************/
queue* Node::GetOutputQueue()
{
    return &this->output_queue;
}

/******************************************************************************
 ** Function    : SetTimeToCreatePacket()
 ** Description : Set the next time to create packet in source node
 ** @param1     : Time to create packet
 ** @return     : No return value.
 *****************************************************************************/
void Node::SetTimeToCreatePacket( int time )
{
    this->time_to_create_packet = time;
}

/******************************************************************************
 ** Function    : GetTimeToCreatePacket() 
 ** Description : Method to get the next time to create packet in source node.
 ** @return     : Returns the next time to create packet in source node.
 *****************************************************************************/
int Node::GetTimeToCreatePacket()
{
    return this->time_to_create_packet;
}

/******************************************************************************
 ** Function    : GetWire()
 ** Description : Method to get all channels( wire ) in a node
 ** @return     : Returns a pointer to all channels( wire ) in a node.
 *****************************************************************************/
connection* Node::GetWire()
{
    return &this->wire;
}

/******************************************************************************
 ** Function    : SetWire()
 ** Description : Method to put data in channel for transmission
 ** @param1     : Interface to which data has to be placed.
 ** @param2     : Packet for transmission
 ** @return     : No return value.
 *****************************************************************************/
void Node::SetWire( int link, packet data )
{
    cout << "SetWire: Link: " << link << " Packet: "<< data.data_size << endl;
    this->wire[ link ] = data;
}

/******************************************************************************
 ** Function    : SetDropCount() 
 ** Description : Method to set the drop count of packets in a node
 ** @param1     : count of packets dropped
 ** @return     : No return value.
 *****************************************************************************/
void Node::SetDropCount( int count )
{
    this->drop_count += count;
}

/******************************************************************************
 ** Function    : GetDropCount() 
 ** Description : Method to get the total drop count in a node
 ** @return     : Returns the total drop count of packets in the node.
 *****************************************************************************/
int Node::GetDropCount()
{
    return this->drop_count;
}

/******************************************************************************
 ** Function    : GeneratePacket
 ** Description : Method to generate a packet
 ** @param1     : Packet structure pointer to be filled with data
 ** @param2     : Source of packet
 ** @param3     : Packet destination
 ** @param3     : Packet size
 ** @param3     : Packet creation time
 ** @return     : Return value is parameter 1
 *****************************************************************************/
void Node::GeneratePacket( packet* data_packet, int src, int dstn, float size, int time  )
{
    if( DEBUG )cout << "Inside GeneratePacket src:" << src << " destn:" << dstn << " size:" << size << " time:"<< time <<endl;
    data_packet->source = src;
    data_packet->destination = dstn;
    data_packet->data_size = size;
    data_packet->time_of_creation = time;
}

/******************************************************************************
 ** Function    : PushPacket()
 ** Description : Method to push data packet to the back of queue
 ** @param1     : The queue
 ** @param2     : The link
 ** @param3     : Data packet
 ** @return     : Returns 0 if success. -1 if failed.
 *****************************************************************************/
int Node::PushPacket( queue* q, int link, packet data )
{
    if( !q->empty() )
    {
	for( auto index = q->begin(); index != q->end();++index )
	{
	    if( index->first == link )
	    {
		if ( index->second.size() <= QUEUE_SIZE  )
		{
		    index->second.push_back( data );
		    return 0;
		}
		else
		{
		    cout << "Queue is full.. Dropping packet" << endl;
		    return -1;
		}
	    }
	}

	packet_vector p;  
	p.push_back( data ); 
	q->insert( { link, p } );
	return 0;
    }
    else
    {
	packet_vector p;

	p.push_back( data );
	q->insert( { link, p } );
	return 0;
    }

    return -1;
}

/******************************************************************************
 ** Function    : PopPacket() 
 ** Description : Method to pop a packet from queue.
 ** @param1     : The queue to be processed
 ** @param2     : The link to be processed
 ** @return     : Returns first packet in a queue specified.
 *****************************************************************************/
packet Node::PopPacket( queue* q, int link )
{
    packet_vector* vec;
    packet popped_packet;

    for( auto index = q->begin(); index != q->end(); ++index )
    {
	popped_packet = {0,0,0,0};
	vec = &index->second;
	if(!vec->empty())
	{
	    if( index->first == link )
	    {
		cout << "\n** Packet to pop **" << endl;

		cout << "Source: " << index->second[ 0 ].source << "\t";
		cout << "Destination: " << index->second[ 0 ].destination << "\t";
		cout << "Packet Size: " << index->second[ 0 ].data_size << "\t";
		cout << "Creation Time: " << index->second[ 0 ].time_of_creation << "\n" <<endl;

		popped_packet = index->second[ 0 ];
		index->second.erase( index->second.begin() );

		return popped_packet;
	    }
	}
    }

    return popped_packet;
}

/******************************************************************************
 ** Function    : PrintQueue() 
 ** Description : The function to print the queues in a node(input/output)
 ** @param1     : The queue to be printed( input or output)
 ** @return     : No return value.
 *****************************************************************************/
void Node::PrintQueue( queue* q )
{
    packet_vector* vec;
    int node_id = getID();

    if( !q->empty() )
    {
	for( auto index = q->begin(); index != q->end(); ++index )
	{
	    cout << "Node: "<< node_id << " Link: " << index->first << endl;
	    vec = &index->second;
	    if(!vec->empty())
	    {
		for( auto idx =vec->begin(); idx != vec->end(); ++idx )
		{
		    cout << "Source: " << idx->source << "\t";
		    cout << "Destination: " << idx->destination << "\t";
		    cout << "Packet Size: " << idx->data_size << "\t"; 
		    cout << "Creation Time: " << idx->time_of_creation << endl <<endl;
		}
	    }

	}
    }
    else
    {
	//cout << "Queue Empty" << endl;
    }
}

/******************************************************************************
 ** Function    : SendToWire
 ** Description : Method to put packet in wire for transmission
 ** @param1     : The interface.
 ** @param2     : The data packet to be transmitted
 ** @return     : No return value.
 *****************************************************************************/
void Node::SendToWire( int link, packet data )
{
    this->wire.insert( make_pair( link, data ));
}

/******************************************************************************
 ** Function    : GetPacketFromWire() 
 ** Description : Method to get packet in the wire
 ** @param1     : The interface from which, we have to get packet
 ** @return     : Returns the packet in channel.
 *****************************************************************************/
packet Node::GetPacketFromWire( int link )
{
    return this->wire.find( link )->second;
}
