/*********************************************************************************
 ** File Name	: Node.h							**
 ** Purpose	: Declare class 'Node' with all the routing functionalities  	**
 ** Author	: Edgar Ceh Varela<eceh@nmsu.edu>, Anju K.James<anju@nmsu.edu>	**
 ** Version	: 1.0								**
 *********************************************************************************/
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

/* HEADERS */
#include <string.h>
#include <list>
#include "common.h"

/* NAMESPACES */

/* CONSTANTS */

/* STATIC VARIABLES */

/* GLOBAL VARIABLES */

/* STRUCTURES */


/* CLASSES */
class Node
{
    int id;			/* No of vertices */ 
    bool is_source;		/* Flag to check whether this node is a source node */
    queue input_queue;		/* Input queue of node */
    queue output_queue;		/* Output queue of node */
    int time_to_create_packet;	/* To store the time to create packet in source node */
    connection wire;		/* Wired connection for data transfer */
    int drop_count;		/* Total number of packets dropped in a router */

    public:

    Node();

    void setID( int id );

    int getID();

    void setSource();

    bool getIsSource();

    queue* GetInputQueue();

    queue* GetOutputQueue();

    void SetTimeToCreatePacket( int time );

    int GetTimeToCreatePacket();

    connection* GetWire();

    void SetWire( int link, packet data );

    void SetDropCount( int count );

    int GetDropCount();

    void GeneratePacket( packet* data_packet, int src, int dstn, float size, int time  );

    int PushPacket( queue* q, int link, packet data );

    packet PopPacket( queue* q, int link );

    void PrintQueue( queue* q );

    void SendToWire( int link, packet data );

    packet GetPacketFromWire( int link );
};

#endif // NODE_H_INCLUDED
