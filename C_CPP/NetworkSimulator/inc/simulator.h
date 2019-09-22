/*********************************************************************************
** File Name	: Simulator.h							**
** Purpose	: Declare class 'Simulator' with all the simulator functionalities 
**		  like run simulator, processing input and output queues,	** 
**		  handling data transmission and the statistics. 	 	**
** Author	: Anju K.James<anju@nmsu.edu>, Edgar Ceh Varela<eceh@nmsu.edu>	**
** Version	: 1.0								**
*********************************************************************************/

#ifndef SIMULATOR_H_INCLUDED
#define SIMULATOR_H_INCLUDED

/* HEADERS */
#include<math.h>
#include "common.h"
#include "node.h"
#include "graph.h"

/* NAMESPACES */

/* CONSTANTS */

/* STATIC VARIABLES */
static unsigned int total_packets_generated		= 0;
static unsigned int total_packets_received		= 0;
static unsigned int max_transmission_time		= 0;
static unsigned int min_transmission_time		= UNSIGNED_INT_MAX;
static unsigned int total_success_transmission_time	= 0;
static unsigned int max_drop_count			= 0;
static unsigned int min_drop_count			= UNSIGNED_INT_MAX;
static unsigned int total_drop_count			= 0;
static float total_transmission_time			= 0.0;
static unsigned int total_transmissions			= 0;

/* GLOBAL VARIABLES */

/* STRUCTURES */

/* CLASSES */
class Simulator
{
    public:

        Simulator();               
        static int getRandomBetween( int x, int y );

        static int getRandomTime();

        static float getUniformRandomVar();

	static int getDelay();

	void SetSourceNodes( Node nodes[], int count, src_destn_pair* pairs );

	void CreatePacketInSourceNodes( int node_count, Node nodes[], src_destn_pair* pairs, Graph* graph, int time );

	void Init( int node_count, Node nodes[], src_destn_pair* pairs, Graph* graph );

	void ProcessOutputQueues( Node nodes[], int node_count, int time, Graph* graph );

	void ProcessInputQueues( Node nodes[], int node_count, int time, Graph* graph );

	void DataTransmission( Node nodes[], int node_count, int time, Graph* graph );

	void RunSimulator( Node nodes[], int node_count, Graph* graph, src_destn_pair* pairs );

	void GenerateStatistics( Node nodes[], int node_count );

	void InitializeSimulator( int node_count, src_destn_pair* pairs, Graph* graph );
};

#endif // SIMULATOR_H_INCLUDED
