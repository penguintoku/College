#include <iostream>
#include <vector>
#include <algorithm>

void partB1();
bool partB2_1();
bool partB2_2();


void partB1(){
	/**
	For the first part of the Part B assignment
	Finding the minimium courses needed for gived courses.
	**/

	//Initialize the course into enums for easy access to the array
	//We add the allCS for the full array
	enum {start, cs1, cs2, cs3, cs4, cs5, cs6, cs7, cs8,
	 cs9, cs10, cs11, cs12, cs13, cs14, cs15, allCS};

	bool edge[allCS][allCS];

	//initialize all to false
	for(int i = 0; i < allCS; i++){
		for(int j = 0; j < allCS; j++){
			edge[i][j] = false;
		}
	}

	//make edges corresonding to the prereq
	edge[start][cs1] = true;
	edge[start][cs2] = true;
	edge[start][cs3] = true;
	edge[cs1][cs6] = true;
	edge[cs2][cs4] = true;
	edge[cs3][cs6] = true;
	edge[cs3][cs12] = true;
	edge[cs4][cs5] = true;
	edge[cs4][cs7] = true;
	edge[cs4][cs14] = true;
	edge[cs5][cs8] = true;
	edge[cs6][cs8] = true;
	edge[cs6][cs13] = true;
	edge[cs7][cs9] = true;
	edge[cs8][cs11] = true;
	edge[cs9][cs10] = true;
	edge[cs14][cs15] = true;

	//make a vector
	std::vector<unsigned int> qCS;
	std::vector<unsigned int> distance(allCS, 0);
	bool visited[allCS];
	for(int i = 0; i < allCS; i++){
		visited[i] = false;
	}

	//put the start node in the queue
	qCS.push_back(start);


	//start the BFS
	while(!qCS.empty()){
		//have the first value be the head node
		unsigned int head = qCS.front();
		visited[head] = true;
		for(int i = 0; i < allCS; i++){
			//check if there is an edge
			if((edge[head][i] == true) && (visited[i] == false)){
				//push the connected nodes
				qCS.push_back(i);
				visited[i] = true;
				//the distance is from the parent
				distance[i] = distance[head]+1;
			}
		}
		//pop the head since we are done with it
		qCS.erase(qCS.begin());
	}
	std::cout << "The minimum semester required: ";
	std::cout << *std::max_element(distance.begin(), distance.end()) << std:: endl;
}

bool partB2_1(){
	/**
	For the second part of the Part B assignment
	If there exists a cycle in a given graph.
	**/

	//Initialize the course into enums for easy access to the array
	//We add the allCS for the full array
	enum {x1, y1, x3, y2, x2, y3, graph1All};

	bool graph1edge[graph1All][graph1All];

	//initialize all to false
	for(int i = 0; i < graph1All; i++){
		for(int j = 0; j < graph1All; j++){
			graph1edge[i][j] = false;
		}
	}

	//make edges corresonding to the undirected graph
	graph1edge[x1][y1] = true;
	graph1edge[y1][x1] = true;
	
	graph1edge[x1][y2] = true;
	graph1edge[y2][x1] = true;

	graph1edge[y1][x2] = true;
	graph1edge[x2][y1] = true;
	
	graph1edge[y1][x3] = true;
	graph1edge[x3][y1] = true;

	graph1edge[y2][x2] = true;
	graph1edge[x2][y2] = true;

	graph1edge[x3][y3] = true;
	graph1edge[y3][x3] = true;

	//make a vector
	std::vector<unsigned int> graph1;
	std::vector<int> parent(graph1All, -1);

	bool graph1Visit[graph1All];
	for(int i = 0; i < graph1All; i++){
		graph1Visit[i] = false;
	}

	//put the start node in the queue
	graph1.push_back(x1);

	//start the BFS
	while(!graph1.empty()){
		//have the first value be the head node
		unsigned int head = graph1.front();
		graph1Visit[head] = true;
		for(int i = 0; i < graph1All; i++){
			//check if there is an edge
			if((graph1edge[head][i] == true) && (graph1Visit[i] == false)){
				//push the connected nodes
				graph1.push_back(i);
				graph1Visit[i] = true;
				parent[i] = head;
			}
			else if((graph1edge[head][i] == true) && (graph1Visit[i] == true) && (parent[head] != i)){
				return true;
			}
		}
		//pop the head since we are done with it
		graph1.erase(graph1.begin());
	}
	return false;
}

bool partB2_2(){
	/**
	For the second part of the Part B assignment
	If there exists a cycle in a given graph.
	**/

	//Initialize the course into enums for easy access to the array
	//We add the allCS for the full array
	enum {a, b, c, d, graph2All};

	bool graph2edge[graph2All][graph2All];

	//initialize all to false
	for(int i = 0; i < graph2All; i++){
		for(int j = 0; j < graph2All; j++){
			graph2edge[i][j] = false;
		}
	}

	//make edges corresonding to the undirected graph
	graph2edge[a][b] = true;
	graph2edge[b][a] = true;
	
	graph2edge[a][c] = true;
	graph2edge[c][a] = true;

	graph2edge[a][d] = true;
	graph2edge[d][a] = true;
	
	graph2edge[b][d] = true;
	graph2edge[d][b] = true;
	
	graph2edge[c][b] = true;
	graph2edge[b][c] = true;

	graph2edge[c][d] = true;
	graph2edge[d][c] = true;

	//make a vector
	std::vector<unsigned int> graph2;
	std::vector<int> parent(graph2All, -1);

	bool graph2Visit[graph2All];
	for(int i = 0; i < graph2All; i++){
		graph2Visit[i] = false;
	}

	//put the start node in the queue
	graph2.push_back(a);

	//start the BFS
	while(!graph2.empty()){
		//have the first value be the head node
		unsigned int head = graph2.front();
		graph2Visit[head] = true;
		for(int i = 0; i < graph2All; i++){
			//check if there is an edge
			if((graph2edge[head][i] == true) && (graph2Visit[i] == false)){
				//push the connected nodes
				graph2.push_back(i);
				graph2Visit[i] = true;
				parent[i] = head;
			}
			else if((graph2edge[head][i] == true) && (graph2Visit[i] == true) && (parent[head] != i)){
				return true;
			}
		}
		//pop the head since we are done with it
		graph2.erase(graph2.begin());
	}
	return false;
}

int main(){
	
	partB1();
	
	partB2_1() ? std::cout << "Yes" << std::endl:
				std::cout << "No" << std::endl;

	partB2_2() ? std::cout << "Yes" << std::endl:
				std::cout << "No" << std::endl;

	return 0;
}