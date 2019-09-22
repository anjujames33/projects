/* Readme.txt */


1. Usage :

	a. $ cd NetworkSimulator
	b. $ make clean // 'bin' and 'obj' directories will be removed.
	c. $ make // binary will be created in 'bin' folder 
	d. $ ./bin/network_simulator <seed> [path/graph_file]

	For example:	$./network_simulator 5
			$./network_simulator 5 network.txt

Note:
-----
	a. seed = Random integer number
	b. path/graph_file = The path of graph file. This is an optional parameter. 
	c. program will generate network file 'network.txt' in the same location from 'where we are executing the binary'
	d. The program will read the graph file provided and process it, if it is a fully connected graph information. 
	   Else it will throw error and exit the program. 

2. Folder Structure :

	NetworkSimulator
	├── bin
	│   └── network_simulator
	├── inc
	│   ├── common.h	//Common header files, variables, structures
	│   ├── graph.h
	│   ├── node.h
	│   └── simulator.h
	├── Makefile
	├── network.txt		//Graph file generated on first execution of binary
	├── obj
	│   ├── graph.o
	│   ├── main.o
	│   ├── node.o
	│   └── simulator.o
	├── Readme.txt
	└── src
	    ├── graph.cpp
	    ├── main.cpp
	    ├── node.cpp
	    └── simulator.cpp


3. Classes Used :
	
	a. Graph 
		The 'Graph' class handles the creation of a fully connected graph.
		Creation of adjacency list, global routing table, bandwidth etc.

	b. Node
		The 'Node' class defines a node/router and its functionalities such as
		queues in a node, processing of queues etc.
 
	c. Simulator
		The 'Simulator class defines the network simulator.
		It includes the various functionalities of simulator such as 
		running simulator, handling data transmission between channel and input output queues.
		Also the statistics.

4. Output :
	
	a. 'Statistics' will be displayed at the end of console logs. 
	b. The log for all functionality at time 't' has been displayed separately in console.

5. Code Flow :

	a. main.cpp -> main()
	b. graph.cpp -> InitGraph()
	c. simulator.cpp -> InitializeSimulator()


6. Design Details:

	a. The adjacency list is used to calculate the Connected Componnets (CC) of the graph. A fully connected network must have only one Connected Component.
	b. Randomly pick 20 pair of nodes. The first node in the pair will be used as a source node, and the second as the destination node.
	c. To calculate the shortest path between source and destination, we use the Floyd-Warshall algorithm. The weight for each link is considered as '1'
	d. Map & Vectors are used instead of arrays for queues since size is dynamically varying.
	e. Global variables, constants and typedefs are defined in a common header file 'common.h'
	f. At time=1, creating packets in all source nodes. After that, packets are created using Poisson distribution. 
	g. Packets are dropped in input and output queues if queue size is reached 30.
	h. 'Transmission' is considered as movement of packet from one node to other.
	i. 'Complete Transmission' is considered as the movement of packet from source to destination. 
	j. If the packet(size) is bigger than the channel bandwidth, then waiting time in channel is calculated as 'packet size / bandwidth' and rounded to next integer.
	   This step attempts to simulate the packet splitting for data transmission.de.cpp
	k. All the function comments/descriptions has been added in .cpp files


/* End */
