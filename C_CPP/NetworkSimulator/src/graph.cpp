/*********************************************************************************
** File Name	: grap.cpp							**
** Purpose	: Defines class 'Graph'					 	**
** Author	: Edgar Ceh Varela<eceh@nmsu.edu>, Anju K.James<anju@nmsu.edu>	**
** Version	: 1.0								**
*********************************************************************************/

/* HEADERS */

#include "graph.h"
#include "node.h"
#include "simulator.h"

/* FUNCTIONS */

/******************************************************************************
 ** Function	: ConnectedComponents() 
 ** Description	: Method to print connected components in a undirected graph
 ** @return	: No return value.
 *****************************************************************************/
void Graph::ConnectedComponents()
{
    //Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int v = 0; v < V; v++)
    {
        visited[ v ] = false;
    }

    int cc_counter = 0;

    for (int v = 0; v < V; v++)
    {
        if( visited[ v ] == false )
        {
            cout << "Connected components: " << cc_counter << ": ";
            cc_counter = cc_counter + 1;

            //print all reachable vertices from v
            DFS( v, visited, cc_counter );
            cout << "\n";
        }
    }
}

/******************************************************************************
 ** Function	: DFS() 
 ** Description	: Depth First Search for finding connected components
 ** @param1 	: Node id
 ** @param2 	: Flag to identify if the node 'v' is visited.
 ** @param3 	: Number of connected components
 ** @return	: No return value.
 *****************************************************************************/
void Graph::DFS( int v, bool visited[], int cc_counter )
{
    //Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";

    // Check if key exits, if YES, get the vector, update it with v, and update key
    // If NO, create vector with v, and create pair ( v, vector )
    if( ccomponents->count( cc_counter ) > 0 )
    {
	//The key ( source ) exists. Find vector for the key
	vector<int> temp;
	temp = ccomponents->find( cc_counter )->second;

	//Add destination to the vector,
	temp.push_back( v );

	//Update the value for key ( source )
	ccomponents->at( cc_counter ) = temp;
    }
    else
    {
	//Create a new vector. and insert the destination in it.
	vector<int> temp;
	temp.push_back( v );

	//Add key:value ( source:destination ) pair
	ccomponents->insert( make_pair( cc_counter, temp ) );
    }

    //Recur for all the vertices adjacent to this vertex
    set<int>::iterator i;
    for( i = adjS[ v ].begin(); i != adjS[ v ].end(); ++i )
    {
	if( !visited[ *i ] )
	{
	    DFS( *i, visited, cc_counter );
	}
    }
}

/******************************************************************************
 ** Function	: GetNumberConnectedComponents()
 ** Description	: Method to retrieve all the connected components
 ** @return	: Returns the number of connected components.
 *****************************************************************************/
int Graph::GetNumberConnectedComponents()
{
    int totalCC = 0;
    totalCC = ccomponents->size();

    return totalCC;
}

/******************************************************************************
 ** Function	: CheckIfConnected()
 ** Description	: Method to check if the graph is connected. If it is not 
 ** 		  a fully connected graph, connect it
 ** @return	: No return value.
 *****************************************************************************/
void Graph::CheckIfConnected()
{
    int totalCC = this->GetNumberConnectedComponents();
    cout << "There are " << totalCC << " connected components" << endl; 

    if( totalCC != 1 )
    {
        //We need to link these connected components to create a single network
        this->LinkCC();
    }
    else
    {
        cout << "Get Links from the Adjacency list" << endl;
        this->GetLinksFromAdjList();
    }
}

/******************************************************************************
 ** Function	: Graph()
 ** Description	: Constructor
 ** @param1 	: Total number of nodes
 ** @return	: No return value.
 *****************************************************************************/
Graph::Graph( int V )
{
    this->V = V;
    this->E = 0;
    this->maxEdgesPerNode = V - 1;
    adj = new list<int>[V];

    nextPath = new int *[ V ];			
    linkDelays = new int *[ V ];		
    linkBandwidth = new float *[ V ];		
    time_to_process_wire = new int *[ V ];	
    adjS = new set<int>[ V ];
    links = new map<int, set<int> >;
    pairs = new map<int, vector<int> >;
    ccomponents = new map<int, vector<int> >;
    nextHops = new map<int, vector<int> >;
}

/******************************************************************************
 ** Function	: Graph() 
 ** Description	: Constructor with number of source/destination nodes
 ** @param1 	: Total number of nodes
 ** @param2 	: Number of source/destination nodes
 ** @return	: No return value.
 *****************************************************************************/
Graph::Graph( int V, int sn )
{
    this->V = V;
    this->sn = sn;
    this->E = 0;
    this->maxEdgesPerNode = V-1;

    adj = new list<int>[ V ];
    nextPath = new int *[ V ];        
    linkDelays = new int *[ V ];      
    linkBandwidth = new float *[ V ];  
    time_to_process_wire = new int *[ V ];
    adjS = new set<int>[ V ];
    links = new map<int, set<int> >;
    pairs = new map<int, vector<int> >;
    ccomponents = new map<int, vector<int> >;
    nextHops = new map<int, vector<int> >;
}

/******************************************************************************
 ** Function	: AddEdge() 
 ** Description	: Method to add an undirected edge to the adjacency list
 ** @param1 	: Source
 ** @param2 	: Destination
 ** @return	: No return value.
 *****************************************************************************/
void Graph::AddEdge( int v, int w )
{
    adjS[v].insert( w );
    adjS[w].insert( v );
}

/******************************************************************************
 ** Function	: LinkCC()
 ** Description	: Method to link connected componnents
 ** @return	: No return value.
 *****************************************************************************/
void Graph::LinkCC()
{
    int total_ccomponents = GetNumberConnectedComponents();
    cout << "~ Total CC = " << total_ccomponents << endl;

    for( int cc = 1; cc < total_ccomponents; cc++ )
    {
        vector<int> temp1;
        temp1 = ccomponents->find( cc )->second;  /////
        int size_ccomponents1 = temp1.size();

        //from these nodes, pick one random index
        int idx1 = Simulator::getRandomBetween( 0, size_ccomponents1-1 );
        int node1 = temp1[ idx1 ];

        int next_cc = cc + 1;
        vector<int> temp2;
        temp2 = ccomponents->find( next_cc )->second;
        int size_ccomponents2 = temp2.size();

        //from these nodes, pick one random index
        int idx2 = Simulator::getRandomBetween( 0, size_ccomponents2-1 );
        int node2 = temp2[ idx2 ];

        this->AddEdge( node1, node2 );
    }

    //We need to Check if now is fully connected
    this->ccomponents->clear();
    this->ConnectedComponents();
    this->CheckIfConnected();
}

/******************************************************************************
 ** Function	: PrintGraph() 
 ** Description	: Method to print the adjacency list representation of graph
 ** @return	: No return value.
 *****************************************************************************/
void Graph::PrintGraph()
{
    for( int v = 0; v < V; ++v )
    {
        cout << "\n Adjacency list of vertex " << v << "\n links to ";
        set<int>::iterator i;
        for( i = adjS[ v ].begin(); i != adjS[ v ].end(); ++i )
           cout << "-> " << *i;
        cout << "\n";
    }
}

/******************************************************************************
 ** Function	: GetMaxEdgesPerNode() 
 ** Description	: Method to return the maximum edges per node
 ** @return	: Returns the maximum edges per node.
 *****************************************************************************/
int Graph::GetMaxEdgesPerNode()
{
    return maxEdgesPerNode;
}

/******************************************************************************
 ** Function	: GenerateRandomLinks()
 ** Description	: Method for Random Links generations
 ** @return	: No return value.
 *****************************************************************************/
void Graph::GenerateRandomLinks()
{
    for( int v = 0; v < V; v++ )
    {
	int maxEdges = this->GetMaxEdgesPerNode();
	int totalLinks = Simulator::getRandomBetween( 1, maxEdges );

	if( DEBUG )cout << "Random links for node " << v << " = " << totalLinks << endl;

        set<int> nodeLinks;
	while ( nodeLinks.size() < totalLinks )
	{
	    int linkedNode = Simulator::getRandomBetween( 0,V-1 );
	    if( linkedNode == v )
	    {
		continue;
	    }
	    else
	    {
		nodeLinks.insert( linkedNode );
	    }
	}

	links->insert( make_pair( v, nodeLinks ) );
    }

    map<int, set<int> >::iterator map_it;
    set<int>::iterator set_it;

    cout << "We formed the following links" << endl;
    for( map_it = links->begin(); map_it != links->end(); ++map_it )
    {
	for( set_it = map_it->second.begin(); set_it != map_it->second.end(); ++set_it )
	{
	    cout << map_it->first << "<==>"<< *set_it << " ";

	    // create the adjacency list entry
	    this->AddEdge( map_it->first, *set_it );
	}

	cout << endl;
    }
}

/******************************************************************************
 ** Function	: GetLinksFromAdjList() 
 ** Description	: Method to get the links given the adjacency list
 ** @return	: No return value.
 *****************************************************************************/
void Graph::GetLinksFromAdjList()
{
    links->clear();

    //traverse the adj list
    for( int v = 0; v < V; ++v )
    {
        set<int> temp;

        temp = adjS[ v ];
        links->insert( make_pair( v, temp ) );
    }
}

/******************************************************************************
 ** Function	: GetLinksDelays() 
 ** Description	: Method to get a matix with the link delays
 ** @return	: No return value.
 *****************************************************************************/
void Graph::GetLinksDelays()
{
    for( int i = 0; i < V; i++ )
    {
        linkDelays[ i ] = new int[ V ];
    }

    for( int i = 0; i < V; i++ )
    {
        for( int j = 0; j < V; j++ )
        {
            linkDelays[ i ][ j ] = -1;
        }
    }

    map<int, set<int> >::iterator map_it;
    set<int>::iterator set_it;

    // Iterate through the links and for each link get a delay time
    for(map_it = links->begin(); map_it != links->end(); ++map_it)
    {
        for( set_it = map_it->second.begin() ; set_it != map_it->second.end(); ++set_it )
        {
            int u = map_it->first;
            int v = *set_it;
            int delay = Simulator::getDelay();
            linkDelays[ u ][ v ] = delay;
            linkDelays[ v ][ u ] = delay;
        }
    }

    cout << "Delay between links" << endl;
    for( int i = 0; i < V; i++ )
    {
        for( int j = 0; j < V; j++ )
        {
            cout << linkDelays[ i ][ j ] << " ";
        }
        cout << endl;
    }
}

/******************************************************************************
 ** Function	: GetLinksBandwidth() 
 ** Description	: Method to calculate the bandwidth of links using uniform 
 ** 		  distribution.
 ** @return	: No return value.
 *****************************************************************************/
void Graph::GetLinksBandwidth()
{
    for( int i = 0; i < V; i++ )
    {
        linkBandwidth[ i ] = new float[ V ];
    }

    for( int i = 0; i < V; i++ )
    {
        for( int j = 0; j < V; j++ )
        {
            linkBandwidth[ i ][ j ] = 0;
        }
    }

    map<int, set<int> >::iterator map_it;
    set<int>::iterator set_it;

    // Iterate through the links and for each link get a delay time
    for(map_it = links->begin(); map_it != links->end(); ++map_it)
    {
        for( set_it = map_it->second.begin() ; set_it != map_it->second.end(); ++set_it )
        {
            int u = map_it->first;
            int v = *set_it;
            float bandwidth = Simulator::getUniformRandomVar();
            linkBandwidth[ u ][ v ] = bandwidth;
            linkBandwidth[ v ][ u ] = bandwidth;
        }
    }

    cout << "Bandwidth between links" << endl;
    for( int i = 0; i < V; i++ )
    {
        for( int j = 0; j < V; j++ )
        {
            cout << linkBandwidth[ i ][ j ] << " ";
        }
        cout << endl;
    }
}

/******************************************************************************
 ** Function	: WriteGraphToFile() 
 ** Description	: Method to write the graph to a text file
 ** @return	: No return value.
 *****************************************************************************/
void Graph::WriteGraphToFile()
{
    // Array to store the links, initialized to all 0s
    int linksArray[ V ][ V ] = {};
    ofstream myfile("network.txt");
    map<int, set<int> >::iterator map_it;
    set<int>::iterator set_it;

    for( map_it = links->begin(); map_it != links->end(); ++map_it )
    {
	cout << "Node " << map_it->first << " is connected to nodes: " << endl;

	for( set_it = map_it->second.begin(); set_it != map_it->second.end(); ++set_it )
	{
	    cout << map_it->first << "<=>"<< *set_it << "\n";
	    linksArray[ map_it->first ][ *set_it ] = 1; // Put 1 where there is a link
	    linksArray[ *set_it ][ map_it->first ] = 1;
	}
    }

    // Traverse the half ot the array, and if there is 1 then is a link. Save it!
    for( int i = 0; i < V; i++ )
    {
	for( int j = i + 1; j < V; j++ )
	{
	    if( linksArray[ i ][ j ] == 1 )
	    {
		E = E + 1;
	    }
	}
    }

    myfile << V << " " << E << "\n";

    for( int i = 0; i < V; i++ )
    {
	for( int j = i + 1; j < V; j++ )
	{
	    if( linksArray[ i ][ j ] == 1 )
	    {
		myfile << i << " "<< j << "\n";
	    }
	}
    }

    //Write a delimiter
    myfile << "**\n";

    cout << "There are " << E << " links in total" << endl;
    myfile.close();
}

/******************************************************************************
 ** Function	: PickSourceDestinationNodes() 
 ** Description	: Method to select the source and destintion nodes
 ** @return	: No return value.
 *****************************************************************************/
void Graph::PickSourceDestinationNodes()
{
    int countPairs = 0;

    while ( countPairs < sn )
    {
	int source = Simulator::getRandomBetween( 0, V-1 );
	int destination = Simulator::getRandomBetween( 0, V-1 );

	cout << "Pair to try " << source << "=" << destination << endl;

	if( source == destination )
	{
	    continue;
	}

	//source != destination find if source in map as key
	if( pairs->count( source ) > 0 )
	{
	    // Force different source nodes ( i.e. not the same source to 2+ different destination )
	    continue;

	    // The key ( source ) exists for that key obtain the vector
	    vector<int> temp;
	    temp = pairs->find( source )->second;

	    // check if for that source, already has that destination
	    if( find( temp.begin(), temp.end(), destination ) != temp.end() )
	    {
		// we found destination inside the vector means that the source-destination pair exists already
		continue;
	    }
	    else
	    {
		// if we did not find it inside the vector, create new  pair of source-destination
		temp.push_back( destination );
		pairs->at( source ) = temp;

		// New pair, so inrement the counting
		countPairs = countPairs + 1;
	    }
	}
	else
	{
	    // The key ( source ) does not exist. create a new vector. and insert the destination in it.
	    vector<int> temp;
	    temp.push_back( destination );
	    pairs->insert( make_pair( source, temp ) );

	    // That is a new pair, so inrement the counting
	    countPairs = countPairs + 1;
	}
    }

    // Let's iterate though the map to count if we have the number of pairs required
    map<int, vector<int> >::iterator map_it;
    vector<int>::iterator vec_it;

    int counter = 1;
    for( map_it = pairs->begin(); map_it != pairs->end(); ++map_it )
    {
	for( vec_it = map_it->second.begin(); vec_it != map_it->second.end(); ++vec_it )
	{
	    cout << "[" << counter << "] " << map_it->first << " "<< *vec_it << "\n";
	    counter = counter + 1;
	}
    }
}

/******************************************************************************
 ** Function	: SolveFloydWarshall() 
 ** Description	: Method for the Floyd-Warshall algoritim
 ** @return	: No return value.
 *****************************************************************************/
void Graph::SolveFloydWarshall()
{
    int FW_Array[ V ][ V ] = { };
    map<int, set<int> >::iterator map_it;
    set<int>::iterator set_it;

    // Initialize array with "INFINITE" values for all cells
    for( int i = 0; i < V; i++ )
    {
	for( int j = 0; j < V; j++ )
	{
	    FW_Array[ i ][ j ] = INT_MAX;
	}
    }

    // Put 1 where there is a link
    for( map_it = links->begin(); map_it != links->end(); ++map_it )
    {
	for( set_it = map_it->second.begin(); set_it != map_it->second.end(); ++set_it )
	{
	    FW_Array[ map_it->first ][ *set_it ] = 1; // Put 1 where there is a link
	    FW_Array[ *set_it ][ map_it->first ] = 1;
	}
    }

    int cost[V][V]= { };
    int path[V][V]= { };
    // initialize cost[] and path[]
    for( int v = 0; v < V; v++ )
    {
	for( int u = 0; u < V; u++ )
	{
	    cost[ v ][ u ] = FW_Array[ v ][ u ];

	    if( v == u )
	    {
		path[ v ][ u ] = 0;
	    }
	    else if( cost[ v ][ u ] != INT_MAX )
	    {
		path[ v ][ u ] = v;
	    }
	    else
	    {
		path[ v ][ u ] = -1;
	    }
	}
    }

    // The dynamic programming algorithm
    for( int k = 0; k < V; k++ )
    {
	for( int v = 0; v < V; v++ )
	{
	    for( int u = 0; u < V; u++ )
	    {
		// If vertex k is on the shortest path from v to u,
		// then update the value of cost[ v ][ u ], path[ v ][ u ]
		if( cost[ v ][ k ] != INT_MAX && cost[ k ][ u ] != INT_MAX
			&& ( cost[ v ][ k ] + cost[ k ][ u ] ) < cost[ v ][ u ] )
		{
		    cost[ v ][ u ] = cost[ v ][ k ] + cost[ k ][ u ];
		    path[ v ][ u ] = path[ k ][ u ];
		}
	    }

	    // if diagonal elements become negative, the
	    // graph contains a negative weight cycle
	    if( cost[ v ][ v ] < 0 )
	    {
		return;
	    }
	}
    }

    // print the cost matrix
    for( int v = 0; v < V; v++ )
    {
	for( int u = 0; u < V; u++ )
	{
	    if( cost[ v ][ u ] == INT_MAX )
		cout << setw( 5 ) << "inf";
	    else
		cout << setw( 5 ) << cost[ v ][ u ];
	}
	cout << endl;
    }
    cout << endl;

    // Make a copy of path[][] so it can be passed
    int **mypath;
    mypath = new int *[ V ];
    for( int i = 0; i < V; i++ )
    {
	mypath[ i ] = new int[ V ];
    }

    for( int i = 0; i < V; i++ )
    {
	for( int j = 0; j < V; j++ )
	{
	    mypath[ i ][ j ] = path[ i ][ j ];
	}
    }

    // Initialize the nextPath ( global routing table ) with -1
    for( int i = 0; i < V; i++ )
    {
	nextPath[ i ] = new int[ V ];
    }

    for( int i = 0; i < V; i++ )
    {
	for( int j = 0; j < V; j++ )
	{
	    nextPath[ i ][ j ] = -1;
	}
    }

    // Print out
    for( int v = 0; v < V; v++ )
    {
	for( int u = 0; u < V; u++ )
	{
	    if( u != v && path[ v ][ u ] != -1 )
	    {
		PrintFWPathTest( mypath, v, u, nextPath );
	    }
	}
    }

    // Print the nextPath ( global routing table )
    cout<< "Next Hop array" << endl;
    for( int v = 0; v < V; v++ )
    {
	for( int u = 0; u < V; u++ )
	{
	    int value = nextPath[ v ][ u ];
	    if( value == -1 )
	    {
		nextPath[ v ][ u ] = u;
	    }
	    cout << nextPath[ v ][ u ] <<  " ";
	}
	cout << endl;
    }
}

/******************************************************************************
 ** Function	: PrintFWPathTest() 
 ** Description	: Method that recursively adds the next hop in the nextPath
 ** 		  ( global routing table ) matrix
 ** @param1 	: 2D array with weight of links
 ** @param2 	: Source node
 ** @param3 	: Destination node
 ** @param3 	: 2D array with next hopes
 ** @return	: No return value.
 *****************************************************************************/
void Graph::PrintFWPathTest( int **path, int v, int u, int **nextPath )
{
    if( path[ v ][ u ] == v )
    {
        return;
    }

    PrintFWPathTest( path, v, path[ v ][ u ], nextPath );
    nextPath[ v ][ u ] = path[ v ][ u ];
}

/******************************************************************************
 ** Function	: DisplayNodeIDs()
 ** Description	: Print all nodes and ids
 ** @param1 	: Array of all nodes
 ** @param2 	: Total node count
 ** @return	: No return value.
 *****************************************************************************/
void Graph::DisplayNodeIDs( Node graph_nodes[], int node_count )
{
    for( int i = 0; i < node_count; i++ )
    {
	int id = graph_nodes[ i ].getID();
	cout << "Node: " << i << ", ID: " << id << endl;
    }
}

/******************************************************************************
 ** Function	: InitChannelProcessingTime() 
 ** Description	: Initialise channel processing time for all nodes with 0 
 ** @return	: No return value.
 *****************************************************************************/
void Graph::InitChannelProcessingTime()
{
    for( int i = 0; i < V; i++ )
    {
	time_to_process_wire[ i ] = new int[ V ];
    }

    for( int i = 0; i < V; i++ )
    {
	for( int j = 0; j < V; j++ )
	{
	    time_to_process_wire[ i ][ j ] = 0;
	}
    }
}

/******************************************************************************
 ** Function	: GetNextHop()
 ** Description	: Method to get the next hope 
 ** @param1 	: Current node
 ** @param2 	: Packet destination
 ** @return	: Node id of nexthop
 *****************************************************************************/
int Graph::GetNextHop( int current_node, int destination )
{
    return nextPath[ current_node ][ destination ];
}

/******************************************************************************
 ** Function	: GetChannelDelay()
 ** Description	: Method to get the transmission delay of a channel
 ** @param1 	: Channel source
 ** @param2 	: Channel destination
 ** @return	: Return the transmission delay of a channel.
 *****************************************************************************/
int Graph::GetChannelDelay( int current_node, int destination )
{
    return linkDelays[ current_node ][ destination ];
}

/******************************************************************************
 ** Function	: GetChannelBandwidth
 ** Description	: Method to get the bandwidth of a channel
 ** @param1 	: Channel source
 ** @param2 	: Channel destination
 ** @return	: Return the bandwidth of a channel.
 *****************************************************************************/
float Graph::GetChannelBandwidth( int current_node, int destination )
{
    return linkBandwidth[ current_node ][ destination ];
}

/******************************************************************************
 ** Function	: GetChannelTotalDelay()
 ** Description	: Method to get the total channel delay
 ** @param1 	: Channel source
 ** @param2 	: Channel destination
 ** @return	: Returns the total delay of channel.
 *****************************************************************************/
int Graph::GetChannelTotalDelay( int current_node, int destination )
{
    return time_to_process_wire[ current_node ][ destination ];	
}

/******************************************************************************
 ** Function	: SetChannelTotalDelay()
 ** Description	: Method to set the actual channel delay after comparing 
 ** 		  channel bandwidth, packet size and channel delay
 ** @param1 	: Channel source
 ** @param2 	: Channel destination
 ** @param3 	: Total delay of channel
 ** @return	: No return value.
 *****************************************************************************/
void Graph::SetChannelTotalDelay( int current_node, int destination, int total_delay )
{
    time_to_process_wire[ current_node ][ destination ] = total_delay;
}

/******************************************************************************
 ** Function	: InitGraph()
 ** Description	: Initialising the graph with source-destination pairs,
 ** 		  routing table with shortes paths, channel delay and 
 ** 		  bandwidth etc.
 ** @param1 	: Total number of nodes
 ** @return	: No return value.
 *****************************************************************************/
void Graph::InitGraph( int node_count )
{
    Simulator simulator;

    if( DEBUG ) PrintGraph();
    WriteGraphToFile();
    PickSourceDestinationNodes();
    GetLinksFromAdjList();
    SolveFloydWarshall();
    GetLinksDelays();
    GetLinksBandwidth();
    InitChannelProcessingTime();

    //Initialising Simulator 
    simulator.InitializeSimulator( node_count, pairs, this );
}
