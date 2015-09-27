/*
Read the README before starting!
Tokumaru Yahashi
*/

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){
	//Checking in user prompt interface that there exists
	// "inputFile.txt" and "outputFile.txt" which is required in 4.6
	//Thank you CS240!!
	if (argc != 3){
		fprintf(stderr,"Usage: %s inputFile.txt outputFile.txt\n", argv[0]);
		return 1;
	}

	//initialization
	vector<int> input;
	int count = 0;
	ifstream inFile;
	ofstream outFile;
	string input_str;

	//open the input and output file
	inFile.open("inputFile.txt");
	outFile.open("outputFile.txt");

	//read the input file until EOF
	while(!inFile.eof()){
		getline(inFile, input_str);
		//push it in the stack while changing to string
		input.push_back(atoi(input_str.c_str()));
		count++;
	}

	//since there will be an extra zero, pop out the last value
	input.pop_back();
	//use the sort function from algorithm to decrease to increase
	sort(input.begin(), input.end());
	//for each number, we will binary search to find 2 keys that equal another key.
	for(int x = 0; x < count-1; x++){
		for(int y=x+1; y < count-1; y++){
			if(binary_search(input.begin(),input.end(), (input.at(x)+input.at(y)))){
				outFile << (input.at(x)+input.at(y)) << " " << input.at(x) << " " << input.at(y) << endl;
			}
		}
	}

	//Close the input and output files	
	inFile.close();
	outFile.close();
	return 0;
}