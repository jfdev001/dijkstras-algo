/*------------------------------------------------------------------------*
 *Author: Jared Frazier   | Date:11/22/2020
 *Course: CSCI 3110-003   | Due: 11/24/2020
 *Instructor: Dr. Barbosa | Asgn Title: proj8
 *Purpose: Use dijkstra's algorithm for undirected and directed graphs
 *------------------------------------------------------------------------*/

 //HEADER FILES
#include <iostream>
#include <fstream>
#include <string>
#include "graph.h"

int main()
{
    //Vars
    std::ifstream read;
    std::string directed;
    bool b_directed;
    int numVerts, numEdgeRecords, start;
    int from, to;
    double wt;

    //Open file and get first items -- g1 is dir, g2 is undir
    read.open("graph1.txt");
    read >> numVerts >> numEdgeRecords >> start;
    
    //Instantiate graph object
    Graph graph(numVerts);

    //Iterate through file and add edges to the graph
    while (read >> from) {
        read >> to >> wt >> directed;
        if (directed == "false") {
            b_directed = false;
        }
        else {
            b_directed = true;
        }
        graph.addEdge(from, to, wt, b_directed);
    }

    //Find dijkstra path
    graph.DijkstraPaths(start);

    read.close();
    return 0;
}