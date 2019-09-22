/*********************************************************************************
** File Name	: Main.cpp							**
** Purpose	: Network Simulator main() function. Starts execusion here 	**
** Author	: Edgar Ceh Varela<eceh@nmsu.edu>, Anju K.James<anju@nmsu.edu>	**
** Version	: 1.0								**
*********************************************************************************/

/* HEADERS */

#include<iostream>
#include<sstream>
#include<fstream>

#include "graph.h"
#include "node.h"

/* FUNCTIONS */

/******************************************************************************
 ** Function	: GenerateGraph()
 ** Description	: Generates random graph, if graph file is not provided  
 ** @param1 	: Total number of nodes. Defined in common.h
 ** @param2 	: Total number of source nodes. Defined in common.h
 ** @return	: No return value.
 *****************************************************************************/
void GenerateGraph()
{
    //Constructor
    Graph g( INITIAL_NODE_COUNT, SOURCE_NODE_COUNT );

    //Create edges/links between nodes
    g.GenerateRandomLinks();

    //Finds the connected components in the graph
    g.ConnectedComponents();

    //Make the graph fully connected if it is not connected.
    g.CheckIfConnected();

    g.InitGraph( INITIAL_NODE_COUNT );
}

/******************************************************************************
 ** Function	: GenerateGraphFromFile()
 ** Description	: Generates graph from file provided  
 ** @param1 	: Graph file 
 ** @return	: No return value.
 *****************************************************************************/
void GenerateGraphFromFile( char graph_file[] )
{
    int node_count = 0;
    int edge_count = 0;
    int src_node = 0;
    int dstn_node = 0;
    int connected_components = 0;
    ifstream gf( graph_file );

    //Read node count and edge count from graph file
    gf >> node_count >> edge_count;

    //Constructor
    Graph g( node_count, SOURCE_NODE_COUNT );

    //Create edges/links
    for( int i = 0; i < edge_count; i++ )
    {
	gf >> src_node >> dstn_node;
	g.AddEdge( src_node, dstn_node );
    }

    g.ConnectedComponents();
    connected_components = g.GetNumberConnectedComponents();

    //If graph is not fully connected, throw error
    if( connected_components != 1 )
    {
	cout << "Incorrect Graph File.....Not fully connected!!!\n" << endl;
	return;
    }
    else
    {
	g.CheckIfConnected();
    }

    g.InitGraph( node_count );
}

/******************************************************************************
 ** Function	: main()  
 ** Description	: Network simulator starts execusion here. 
 **		  If graph file is provided, graph will be created from file. 
 **		  else, it will create random graph based on parameters 
 **		  specified in inc/common.h
 ** @param1 	: argc - Total number of arguments
 ** @param2 	: argv[] - array of input parameters
 ** @return	: Returns 0 to exit the function.
 *****************************************************************************/
int main( int argc, char* argv[] )
{
    int seed = 0;
    char* graph_file = NULL;

    cout << "~~ Network Simulator ~~" << endl;

    if ( argc == 2 )
    {
        // Convert the string to an int for the random seed
        stringstream seed_arg( argv[1] );
        seed_arg >> seed;
        srand( seed );

        //Generate graph
        GenerateGraph();
    }
    else if ( argc == 3 )
    {
        fstream fs;

        // Convert the string to an int for the random seed
        stringstream seed_arg( argv[1] );
        seed_arg >> seed;
        srand( seed );

        //Read the graph_file to generate graph
        graph_file = argv[2];
        fs.open(graph_file);

        if( fs.fail() )
        {
            cout << "Error: Graph File does not exist: " << graph_file << endl;
            fs.close();
            return 0;
        }
        else if( fs.peek() == std::ifstream::traits_type::eof() )
        {
            cout << "Error: Empty Graph File: " << graph_file << endl;
            fs.close();
            return 0;
        }
        else
        {
            //Generate graph from the input graph file
            GenerateGraphFromFile( graph_file );
        }

        fs.close();
    }
    else
    {
        cout << "Usage: ./<binary_name> <seed> [path/graph_file]" << endl;
        return 0;
    }

    return 0;
}
