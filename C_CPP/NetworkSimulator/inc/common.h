/*********************************************************************************
** File Name	: Common.h							**
** Purpose	: Common header files, variables, structures and functions are 	**
**		  declared in this file.					**
** Author	: Edgar Ceh Varela<eceh@nmsu.edu>, Anju K.James<anju@nmsu.edu>	**
** Version	: 1.0								**
*********************************************************************************/

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

/* HEADERS */
#include <iostream>
#include <ctime> 
#include <vector>
#include <map>

/* NAMESPACES */
using namespace std;

/* CONSTANTS */
#define LAMBDA				0.5
#define DELAY_DISTRIBUTION_START	1
#define DELAY_DISTRIBUTION_STOP		10
#define QUEUE_SIZE			30
#define MAX_NODE_COUNT			150
#define INITIAL_NODE_COUNT		150
#define SOURCE_NODE_COUNT		20
#define SIMULATOR_TIME			1000
#define UNSIGNED_INT_MAX		2147483647
#define DEBUG				0

/* STATIC VARIABLES */

/* GLOBAL VARIABLES */

/* STRUCTURES */
typedef struct Packet
{
    int source;
    int destination;
    float data_size;
    int time_of_creation;
} packet;

typedef std::vector< packet > packet_vector;
typedef std::map< int, packet_vector > queue;
typedef std::map<int, vector<int> > src_destn_pair;
typedef std::map< int, packet > connection;

#endif // COMMON_H_INCLUDED
