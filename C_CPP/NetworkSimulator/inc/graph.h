/*********************************************************************************
 ** File Name	: graph.h							**
 ** Purpose	: Declaration of 'Graph' class which creates a fully connected  **
 **		  graph using adjacency list.					**
 ** Author	: Edgar Ceh Varela<eceh@nmsu.edu>, Anju K.James<anju@nmsu.edu>	**
 ** Version	: 1.0								**
 *********************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

/* HEADERS */
#include <cmath>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <limits.h>
#include <stdint.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

#include "common.h"
#include "node.h"


/* NAMESPACES */
using namespace std;

/* CONSTANTS */

/* STATIC VARIABLES */

/* GLOBAL VARIABLES */

/* STRUCTURES */

/* CLASSES */
class Graph
{
    int V;				/* Number of vertices */
    int E;				/* Number of edges */
    int sn;				/* number of source/destination nodes */
    int maxEdgesPerNode;		/* Maximum number of edges per node */
    list<int> *adj;			/* Adjacency list array */
    set<int> *adjS;			/* Set of adjacency list. Set is used to prevent duplicates */
    map<int, set<int> > *links;		/* Map of random links */
    src_destn_pair *pairs;		/* To store the source destination pair */
    map<int, vector<int> > *ccomponents;/* Map for connected components */
    map<int, vector<int> > *nextHops;	/* To save all the next hops ( overall routing table ) */
    set<int> *sourceNodes;		/* Set of the randomly selected source nodes */
    int **nextPath;			/* Stores the next hops for each node */
    int **linkDelays;			/* Stores the delays between links */
    float **linkBandwidth;		/* Stores the bandwidth between links */
    int **time_to_process_wire;		/* Stores the total delay of all channels */

    /* FUNCTIONS */

    void DFS( int v, bool visited[], int cc_counter );
    void PrintFWPathTest( int **path, int v, int u, int **nextPath );

    public:

    Graph( int V );                      

    Graph( int V, int sn );               

    void AddEdge( int v, int w );

    void ConnectedComponents();

    int GetNumberConnectedComponents();

    void CheckIfConnected();

    int GetMaxEdgesPerNode();

    void LinkCC();

    void PrintGraph();

    void CreateNodeObjects();

    void PrintNodesInfo();

    void GenerateRandomLinks();

    void GetLinksFromAdjList();

    void GetLinksDelays();

    void GetLinksBandwidth();

    void WriteGraphToFile();

    void PickSourceDestinationNodes();

    void SolveFloydWarshall();

    void DisplayNodeIDs( Node graph_nodes[], int node_count );

    void InitChannelProcessingTime();

    void InitGraph( int node_count );

    int GetNextHop( int current_node, int destination );

    int GetChannelDelay( int current_node, int destination );

    float GetChannelBandwidth( int current_node, int destination );

    int GetChannelTotalDelay( int current_node, int destination );

    void SetChannelTotalDelay( int current_node, int destination, int total_delay );

};

#endif // GRAPH_H_INCLUDED
