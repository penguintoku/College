#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <time.h>

using namespace std;

struct point{
	int x, y, z;
};

struct bestPoints{
	int x1, y1, z1;
	int x2, y2, z2;
	double distance;
};

void printCoordinates(vector<point> &coordinates);
bestPoints bruteF(vector<point> &coordinates);
bestPoints divAcon(vector<point> &coordinates, int LB, int RB);


//Put the coords in X order then in Y order
bool compare(const point  &a, const point &b){
	if(a.x < b.x){
		return true;
	}
	else if(a.x > b.x){
		return false;
	}
	else if(a.y < b.y){
		return true;
	}
	return false;
}
int main(int argc, char* argv[]){
	ifstream inFile;
	ofstream outFile;
	stringstream intConvert;
	int result;
	string lineIn;
	vector<point> coordinates;
	clock_t timeA, timeB;

	//Checking in user prompt interface that there exists
	// "inputFile.txt" and "outputFile.txt" which is required
	//Thank you CS240!!
	if (argc != 3){
		fprintf(stderr,"Usage: %s inputFile.txt outputFile.txt\n", argv[0]);
		return 1;
	}

	inFile.open("inputFile.txt");
	outFile.open("outputFile.txt");

	//read the input file until EOF and put values in the vector
	while( getline(inFile, lineIn)){
		intConvert << lineIn;
		point temp;
		intConvert >> result;
		temp.x = result;
		intConvert >> result;
		temp.y = result;
		intConvert >> result;
		temp.z = result;
		coordinates.push_back(temp);
		intConvert.clear();
	}

	//sort the coords
	sort(coordinates.begin(), coordinates.end(), compare);

	//calling the functions and timing them
	timeA = clock();
	bestPoints brute = bruteF(coordinates);
	timeA = clock() - timeA;
	timeB = clock();
	bestPoints dac = divAcon(coordinates, 0, coordinates.size()-1);
	timeB = clock() - timeB;

	//printing to terminal
	cout << endl;
	cout << "Cords are: " << endl;
	cout << brute.x1 << ' ' << brute.y1<< ' ' << brute.z1 <<  endl << brute.x2 << ' ' << brute.y2 << ' ' << brute.z2 <<  endl << "Distance: " << brute.distance <<  endl;
	cout << "Brute Force time: " << (((float)timeA)/CLOCKS_PER_SEC) << endl;
	cout << "Divide and Conquer time: " << (((float)timeB)/CLOCKS_PER_SEC) << endl;
	cout << endl;

	//Printing to output file
	outFile << "Cords are: " << endl;
	outFile << brute.x1 << ' ' << brute.y1<< ' ' << brute.z1 <<  endl << brute.x2 << ' ' << brute.y2 << ' ' << brute.z2 <<  endl << "Distance: " << brute.distance <<  endl;
	outFile << "Brute Force time: " << (((float)timeA)/CLOCKS_PER_SEC) << endl;
	outFile << "Divide and Conquer time: " << (((float)timeB)/CLOCKS_PER_SEC) << endl;
}

//The brute force approach
bestPoints bruteF(vector<point> &coordinates){
	bestPoints best;

	//Initialize the first value
	best.x1 = coordinates[0].x;
	best.y1 = coordinates[0].y;
	best.z1 = coordinates[0].z;
	best.x2 = coordinates[1].x;
	best.y2 = coordinates[1].y;
	best.z2 = coordinates[1].z;

	//Getting the distance of the first value
	double tempx = pow(coordinates[1].x - coordinates[0].x,2);
	double tempy = pow(coordinates[1].y - coordinates[0].y,2);
	double tempz = pow(coordinates[1].z - coordinates[0].z,2);
	best.distance = sqrt(tempx + tempy + tempz);

	//Brute force by checking EVERY value
	for(int x = 0; x < (signed)coordinates.size()-1; x++){
		for(int y = x+1; y < (signed)coordinates.size(); y++){
			double tempx = pow(coordinates[y].x - coordinates[x].x,2);
			double tempy = pow(coordinates[y].y - coordinates[x].y,2);
			double tempz = pow(coordinates[y].z - coordinates[x].z,2);
			double tempDistance = sqrt(tempx + tempy + tempz);

			//If new best cords are found, change it
			if(tempDistance < best.distance){
				best.distance = tempDistance;
				best.x1 = coordinates[x].x;
				best.y1 = coordinates[x].y;
				best.z1 = coordinates[x].z;
				best.x2 = coordinates[y].x;
				best.y2 = coordinates[y].y;
				best.z2 = coordinates[y].z;
			}
		}
	}
	return best;
}

//Recursive divide and conquer approach
bestPoints divAcon(vector<point> &coordinates, int LB, int RB){
	bestPoints best;

	//Initializa the first value
	best.x1 = coordinates[LB].x;
	best.y1 = coordinates[LB].y;
	best.z1 = coordinates[LB].z;
	best.x2 = coordinates[RB].x;
	best.y2 = coordinates[RB].y;
	best.z2 = coordinates[RB].z;

	//Getting the distance of the first value
	double tempx = pow(coordinates[RB].x - coordinates[LB].x,2);
	double tempy = pow(coordinates[RB].y - coordinates[LB].y,2);
	double tempz = pow(coordinates[RB].z - coordinates[LB].z,2);
	double bestDistance = sqrt(tempx + tempy + tempz);
	best.distance = bestDistance;

	//If the blocks are 1 size
	if((RB - LB) == 1){
		best.x1 = coordinates[LB].x;
		best.y1 = coordinates[LB].y;
		best.z1 = coordinates[LB].z;
		best.x2 = coordinates[RB].x;
		best.y2 = coordinates[RB].y;
		best.z2 = coordinates[RB].z;

		double tempx = pow(coordinates[RB].x - coordinates[LB].x,2);
		double tempy = pow(coordinates[RB].y - coordinates[LB].y,2);
		double tempz = pow(coordinates[RB].z - coordinates[LB].z,2);
		double bestDistance = sqrt(tempx + tempy + tempz);
		best.distance = bestDistance;

		return best;

	}
	//If the blocks are 2 sizes
	if((RB - LB)  == 2){
		best.x1 = coordinates[LB].x;
		best.y1 = coordinates[LB].y;
		best.z1 = coordinates[LB].z;
		best.x2 = coordinates[RB-1].x;
		best.y2 = coordinates[RB-1].y;
		best.z2 = coordinates[RB-1].z;

		double tempx = pow(coordinates[RB-1].x - coordinates[LB].x,2);
		double tempy = pow(coordinates[RB-1].y - coordinates[LB].y,2);
		double tempz = pow(coordinates[RB-1].z - coordinates[LB].z,2);
		best.distance = sqrt(tempx + tempy + tempz);

		//
		for(int x = LB; x < RB; x++){
			for(int y = x + 1; y < (signed) coordinates.size(); y++){
				double tempx = pow(coordinates[y].x - coordinates[x].x,2);
				double tempy = pow(coordinates[y].y - coordinates[x].y,2);
				double tempz = pow(coordinates[y].z - coordinates[x].z,2);
				double tempDistance = sqrt(tempx + tempy + tempz);

				//If new best cords are found, change it
				if(tempDistance < best.distance){
					best.x1 = coordinates[x].x;
					best.y1 = coordinates[x].y;
					best.z1 = coordinates[x].z;
					best.x2 = coordinates[y].x;
					best.y2 = coordinates[y].y;
					best.z2 = coordinates[y].z;
					best.distance = tempDistance;
				}
			}
		}
		return best;
	}
	int mid = LB + (RB - LB)/2;
	bestPoints lClosest = divAcon(coordinates, LB, mid);
	bestPoints rClosest = divAcon(coordinates, mid+1, RB);
	if(lClosest.distance < rClosest.distance){
		return lClosest;
	}
	else{
		return rClosest;
	}
}
/*
//Used to see if it was in order from x and then y
void printCoordinates( vector<point> &coordinates){
	for(int x = 0; x < coordinates.size(); x++){
		cout << coordinates[x].x << ' ';
		cout << coordinates[x].y << ' ';
		cout << coordinates[x].z <<  endl;
	}
}
*/