/*
Read the README before starting!!!!
Tokumaru Yahashi
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<deque>
#include<cstdio>

//Struct of edge
struct edge{
	int weight, start, end;
};

//Function Prototype
int find(int current_node, std::deque<int> &parent);
void union_tree(int u, int v, std::deque<int> &parent);
bool comparator(const edge &weight_a, const edge &weight_b);

//The main function
int main(void){

	//Enum for picture assaigning
	enum {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, p20, all_pics};
	
	//create a queue with all -1 
	std::deque<int> parent(all_pics, -1);

	//create vector for the edge
	std::vector<edge> list;
	
	//create the matrix
	int matrix[all_pics][all_pics];


	//Initialize the matrix to all 0's
	for(unsigned int x = 0; x < all_pics; x++){
		for(unsigned int y = 0; y < all_pics; y++){
			matrix[x][y] = 0;
		}
	}

	//assign the weight if conncection exists
	matrix[p1][p2] = 80;
	matrix[p5][p9] = 73;
	matrix[p9][p13] = 69;
	matrix[p2][p3] = 10;
	matrix[p5][p7] = 20;
	matrix[p5][p2] = 74;
	matrix[p9][p18] = 15;
	matrix[p13][p14] = 21;
	matrix[p9][p1] = 92;
	matrix[p13][p2] = 59;
	matrix[p20][p4] = 6;
	matrix[p18][p17] = 17;
	matrix[p11][p3] = 74;
	matrix[p7][p18] = 83;
	matrix[p7][p12] = 27;
	matrix[p1][p10] = 16;
	matrix[p5][p15] = 47;
	matrix[p20][p14] = 94;
	matrix[p14][p18] = 77;
	matrix[p2][p4] = 30;
	matrix[p11][p14] = 62;
	matrix[p3][p20] = 85;
	matrix[p11][p7] = 62;
	matrix[p6][p10] = 87;
	matrix[p12][p15] = 81;
	matrix[p3][p19] = 39;
	matrix[p9][p8] = 45;
	matrix[p19][p4] = 65;
	matrix[p8][p16] = 70;
	matrix[p15][p17] = 64;
	matrix[p1][p11] = 32;
	matrix[p11][p6] = 43;
	matrix[p12][p6] = 87;
	matrix[p12][p19] = 70;
	matrix[p7][p16] = 39;
	matrix[p13][p6] = 22;
	matrix[p4][p16] = 68;
	matrix[p17][p10] = 56;
	matrix[p19][p15] = 71;

	//If there was a connection put in into the vector using the struct
	for(unsigned int x = 0; x < all_pics; x++){
		for(unsigned int y = 0; y < all_pics; y++){
			if(matrix[x][y] > 0){
				edge temp;
				temp.weight = matrix[x][y];
				temp.start = x;
				temp.end = y;
				list.push_back(temp);			
			}
			
		}
	}

	//sort the edge by decreasing order
	std::sort(list.begin(), list.end(), comparator);

	unsigned int x = 0;
	unsigned int y = 0;

	//The Maximum Spanning Tree using Kruskal's Algorithm (Assuming we know how many groups)
	//Change the number from 3~20 groups in this example inorder to get different amount of groups
	while(x < list.size() && y < all_pics - 3){
		if(find(list[x].start, parent) != find(list[x].end, parent)){
			union_tree(list[x].start, list[x].end, parent);
			y++;		
		}
		x++;	
	}

	//Create a vector to check if visited
	std::vector<bool> owned(all_pics, false);
	int group = 1;

	//Display the results depending on how many groups intialized
	for(x = 0; x < parent.size(); x++){
		if(owned[x] != true){	
			owned[x] = true;
			std::cout << group << ": ";
			group++;			
			std::cout << x + 1;
			for(y = x + 1; y < parent.size(); y++){
				if(find(x, parent) == find(y, parent)){
					std::cout << "->" << y + 1;
					owned[y] = true;
				}
			}
			std::cout << std::endl;
		}
	}
	return 0;
}
//End of main function

//Follows the parent nodes until it reaches the root
int find(int current_node, std::deque<int> &parent){
	if(parent[current_node] == -1){	
		return current_node;
	}
	else{
		return find(parent[current_node], parent);
	}
}
//end of find function

//Combines the two trees into one by attaching the root of one to the root to the other
void union_tree(int u, int v, std::deque<int> &parent){
	int u_root = find(u, parent);
	int v_root = find(v, parent);
	parent[u_root] = v_root;
}
//end of union function

//The function that will make the weight in decreasing order
bool comparator(const edge &weight_a, const edge &weight_b){
	return weight_a.weight > weight_b.weight;
};
//end of comparator function