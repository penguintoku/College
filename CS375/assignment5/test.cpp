#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

typedef int vertex_t;
typedef double weight_t;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor{
	vertex_t target;
	weight_t weight;
	neighbor(vertex_t arg_target, weight_t arg_weight)
		: target(arg_target), weight(arg_weight) { }
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;

void DijkstraComputePaths(vertex_t source,
							const adjacency_list_t &adjacency_list,
							std::vector<weight_t> &min_distance,
							std::vector<vertex_t> &previous){
	int n = adjacency_list.size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<weight_t, vertex_t> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while(!vertex_queue.empty()){
		weight_t dist = vertex_queue.begin()->first;
		vertex_t u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());
 
		// Visit each edge exiting u
		const std::vector<neighbor> &neighbors = adjacency_list[u];

		for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
			neighbor_iter != neighbors.end();
			neighbor_iter++)
		{
			vertex_t v = neighbor_iter->target;
			weight_t weight = neighbor_iter->weight;
			weight_t distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(std::make_pair(min_distance[v], v));
				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));
			}
		}
	}
}

std::list<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const std::vector<vertex_t> &previous){
	std::list<vertex_t> path;
	for ( ; vertex != -1; vertex = previous[vertex]){
		path.push_front(vertex);
	}
	return path;
}

int main(){

	//Telling how many nodes there are in the graph
    adjacency_list_t adjacency_list(11);
    
    //assigning all the edges depending on the node
    // a = 0
    adjacency_list[0].push_back(neighbor(9, 1));
    adjacency_list[0].push_back(neighbor(1, 5));
    adjacency_list[0].push_back(neighbor(6, 21));
    adjacency_list[0].push_back(neighbor(4, 12));
    adjacency_list[0].push_back(neighbor(8, 15));
    
    // b = 1
    adjacency_list[1].push_back(neighbor(0, 5));
    adjacency_list[1].push_back(neighbor(6, 18));
    adjacency_list[1].push_back(neighbor(9, 20));
    adjacency_list[1].push_back(neighbor(2, 9));
    
    // c = 2
    adjacency_list[2].push_back(neighbor(1, 9));
    adjacency_list[2].push_back(neighbor(6, 17));
    adjacency_list[2].push_back(neighbor(3, 16));
    adjacency_list[2].push_back(neighbor(10, 8));
    
    // d = 3
    adjacency_list[3].push_back(neighbor(2, 16));
    adjacency_list[3].push_back(neighbor(5, 7));
    adjacency_list[3].push_back(neighbor(7, 14));
    adjacency_list[3].push_back(neighbor(6, 11));
    
    // e = 4
    adjacency_list[4].push_back(neighbor(0, 12));
    adjacency_list[4].push_back(neighbor(4, 2));
    adjacency_list[4].push_back(neighbor(5, 6));
    adjacency_list[4].push_back(neighbor(8, 10));
    
    // f = 5
    adjacency_list[5].push_back(neighbor(7, 4));
    adjacency_list[5].push_back(neighbor(3, 7));    
    adjacency_list[5].push_back(neighbor(4, 6));
    adjacency_list[5].push_back(neighbor(9, 19));
    adjacency_list[5].push_back(neighbor(10, 13));
    
    // g = 6
    adjacency_list[6].push_back(neighbor(0, 21));
    adjacency_list[6].push_back(neighbor(1, 18));    
    adjacency_list[6].push_back(neighbor(2, 17));
    adjacency_list[6].push_back(neighbor(3, 11));
    adjacency_list[6].push_back(neighbor(4, 2));
    adjacency_list[6].push_back(neighbor(7, 3));
    
    // h = 7
    adjacency_list[7].push_back(neighbor(3, 14));
    adjacency_list[7].push_back(neighbor(5, 4));
    adjacency_list[7].push_back(neighbor(6, 3));
    
    // i = 8
    adjacency_list[8].push_back(neighbor(0, 15));
    adjacency_list[8].push_back(neighbor(4, 10));
    
    // j = 9
    adjacency_list[9].push_back(neighbor(0, 1));
    adjacency_list[9].push_back(neighbor(1, 20));
    adjacency_list[9].push_back(neighbor(5, 19));
 
    // i = 10
    adjacency_list[10].push_back(neighbor(2, 8));
    adjacency_list[10].push_back(neighbor(5, 13));


    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    DijkstraComputePaths(0, adjacency_list, min_distance, previous);

    std::cout << "Distance from a to b: " << min_distance[1] << std::endl;
    std::list<vertex_t> path = DijkstraGetShortestPathTo(1, previous);
    std::cout << "Path: ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to c: " << min_distance[2] << std::endl;
    std::list<vertex_t> path2 = DijkstraGetShortestPathTo(2, previous);
    std::cout << "Path: ";
    std::copy(path2.begin(), path2.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to d: " << min_distance[3] << std::endl;
    std::list<vertex_t> path3 = DijkstraGetShortestPathTo(3, previous);
    std::cout << "Path: ";
    std::copy(path3.begin(), path3.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to e: " << min_distance[4] << std::endl;
    std::list<vertex_t> path4 = DijkstraGetShortestPathTo(4, previous);
    std::cout << "Path: ";
    std::copy(path4.begin(), path4.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to f: " << min_distance[5] << std::endl;
    std::list<vertex_t> path5 = DijkstraGetShortestPathTo(5, previous);
    std::cout << "Path: ";
    std::copy(path5.begin(), path5.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to g: " << min_distance[6] << std::endl;
    std::list<vertex_t> path6 = DijkstraGetShortestPathTo(6, previous);
    std::cout << "Path: ";
    std::copy(path6.begin(), path6.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to h: " << min_distance[7] << std::endl;
    std::list<vertex_t> path7 = DijkstraGetShortestPathTo(7, previous);
    std::cout << "Path: ";
    std::copy(path7.begin(), path7.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to i: " << min_distance[8] << std::endl;
    std::list<vertex_t> path8 = DijkstraGetShortestPathTo(8, previous);
    std::cout << "Path: ";
    std::copy(path8.begin(), path8.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to j: " << min_distance[9] << std::endl;
    std::list<vertex_t> path9 = DijkstraGetShortestPathTo(9, previous);
    std::cout << "Path: ";
    std::copy(path9.begin(), path9.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "Distance from a to k: " << min_distance[10] << std::endl;
    std::list<vertex_t> path10 = DijkstraGetShortestPathTo(10, previous);
    std::cout << "Path: ";
    std::copy(path10.begin(), path10.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl; 
    
    return 0;
}