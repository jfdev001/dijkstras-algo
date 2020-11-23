#include "graph.h"

//Constructor -- Construct number of vertices
Graph::Graph(int num){
	numVertices = num;
	adjacent.resize(num); //Allocates indices for adjacency list
}

//AddEdge function -- add an edge to the adjacency list
void Graph::addEdge(int fromVertex, int toVertex, double weight, bool dirEdge) {
	Edge oneway_edge(fromVertex, toVertex, weight); //Construct a new edge
	adjacent[fromVertex].push_back(oneway_edge);    //at least one way
	std::cout << "Edge " << fromVertex << ", " << toVertex << ", " << weight << std::endl;
	if(dirEdge == false) { //undirected edge (both ways)
		Edge otherway_edge(toVertex, fromVertex, weight);
		adjacent[toVertex].push_back(otherway_edge);
		std::cout << "Edge " << toVertex << ", " << fromVertex << ", " << weight << std::endl;
	}
}

//Dijkstra path
void Graph::DijkstraPaths(int sourceVertex) {
	//Local vars
	std::vector<PathNode> costPrev; //Cost-prev data structure
	std::set<std::pair<double, int>> openList; //Min queue for vertices, compares first element (cost) of pair as key

	//Initialize the cost-prev data structure
	costPrev.resize(numVertices); //Resize to number of vertices
	PathNode source, otherThanSource; //Path nodes for source vertex and all other vertexes
	otherThanSource.cost = std::numeric_limits<double>::infinity(); //Set cost to infinity
	otherThanSource.prev = -1; //Other source prev is negative 1
	source.cost = 0; //Set source cost to 0 (no cost associated with "going" to itself)
	source.prev = -1; //Set prev to negative one for both source and others
	for (int i = 0; i < numVertices; i++) {
		if (i != sourceVertex) {
			costPrev[i] = otherThanSource;
		}
	}
	costPrev[sourceVertex] = source; //Set the source vertex

	//Initialize the openList (min queue) with source vertex
	openList.insert(std::make_pair(source.cost, sourceVertex)); // construct a pair key = source.cost and label = sourceVertex

	//Iterate through graph and find shortest path
	while (!openList.empty()) {
		//Remove the min cost vertex (should be first )
		std::pair<double, int> priorityItem = *(openList.begin()); //front of queue -- double cost, int vertex
		openList.erase(openList.begin()); //Delete front of queue

		//Iterate through list of edges for priorityItem vertex (initially sourceVertex list)
		std::list<Edge> priorityItemEdgeList = adjacent[priorityItem.second]; //Contains the list of edges at priorityItem vertex
		for (std::list<Edge>::const_iterator iter = priorityItemEdgeList.begin(),
			end = priorityItemEdgeList.end(); iter != end; ++iter) {
			if (costPrev[iter->v2].cost > priorityItem.first + iter->weight) { //If current COST to the toVertex > sum of cost of priorityItem and weight to toVertex
				costPrev[iter->v2].cost = priorityItem.first + iter->weight; //update costPrev table
				costPrev[iter->v2].prev = priorityItem.second; //Previous node in path to toVertex is now the prioItem node (e.g. 0 --6--> 1) 
				openList.insert(std::make_pair(costPrev[iter->v2].cost, iter->v2)); //Add wt and index to the openList to determine what will be processed next
			}
		}
	}

	//Output shortest paths -- note, the output immediately after
	//iomanip statements determines alignment and separator from that
	std::cout << "\nShortest paths:" << std::endl;
	for (int i = 0; i < costPrev.size(); i++) {
		std::cout << i << " " << " cost: "
			<< std::left << std::setw(10) << costPrev[i].cost
			<< std::left << std::setw(10) << "prev: "
			<< costPrev[i].prev << std::endl;
	}
}

