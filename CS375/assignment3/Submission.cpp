#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

//headers
void distance();
void LCS(string A, string B);
void LCS2(string A, string B, string C);
int max(int A, int B);
int max2(int A, int B, int C);


int main(){

	/**
	This is for the first part of the Programming Part for Assignment 3
	Finding the distance between New York City to Tronto
	**/

	distance();
	
	/**
	This is for the second part of the Programming Part for Assignment 3
	Finding the longest common sequence of two strings
	**/

	string A ("6541254939322816220209974565477289648317");
	string B ("3142522751761601737419090933147067701840");

	LCS(A,B);

	/**
	This is for the third part of the Programming Part for Assignment 3
	Finding the longest common sequence of three strings
	**/

	string C ("2807030561290354259513570160162463275171");


	LCS2(A,B,C);

	return 0;
}

void distance(){

	//Initialize the cities into enums for easy access to the array
	//We add the AllCities for the full array
	enum {Albany, Allentown, Binghamton, Buffalo, Kingston, Montreal, NYC, 
		Rochester, Scranton, Syracuse, Toronto, AllCities};

	//Making a double array for the distance
	unsigned int dist[AllCities][AllCities];

	//initalize all the nodes to 0 if their exists a direct path
	//If their is no direct path, assign to -1
	for(int i = 0; i < AllCities; i++){
		for(int j = 0; j < AllCities; j++){
			if(i == j){
				dist[i][j] = 0;
			}
			else{
				dist[i][j] = -1;
				dist[i][j]/= 2; //This is to avoid the underflow
			}
		}
	}

	//Initialize the direct paths if given in the map from the assignment
	dist[Albany][NYC] = 140;
	dist[Albany][Montreal] = 130;
	dist[Albany][Syracuse] = 100;
	dist[Allentown][NYC] = 70;
	dist[Allentown][Scranton] = 65;
	dist[Binghamton][Scranton] = 60;
	dist[Binghamton][Syracuse] = 70;
	dist[Binghamton][NYC] = 180;
	dist[Buffalo][Rochester] = 60;
	dist[Buffalo][Toronto] = 100;
	dist[Kingston][Montreal] = 160;
	dist[Kingston][Toronto] = 180;
	dist[Kingston][Syracuse] = 65;
	dist[Montreal][Albany] = 130;
	dist[Montreal][Kingston] = 160;
	dist[NYC][Allentown] = 70;
	dist[NYC][Scranton] = 100;
	dist[NYC][Binghamton] = 180;
	dist[NYC][Albany] = 140;
	dist[Rochester][Syracuse] = 70;
	dist[Rochester][Buffalo] = 60;
	dist[Scranton][Binghamton] = 60;
	dist[Scranton][NYC] = 100;
	dist[Scranton][Allentown] = 65;
	dist[Syracuse][Albany] = 100;
	dist[Syracuse][Binghamton] = 70;
	dist[Syracuse][Rochester] = 70;
	dist[Syracuse][Kingston] = 65;
	dist[Toronto][Kingston] = 180;
	dist[Toronto][Buffalo] = 100;

	//Using the Floyd's Algorithm find the shortest distance 
	for(int k = 0; k < AllCities; k++){
		for(int i = 0; i < AllCities; i++){
			for(int j = 0; j < AllCities; j++){
				if((dist[i][k] + dist[k][j]) < dist[i][j]){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}

	//Print out the shortest distance between New York City and Tronto
	cout << endl;
	cout << "The shortest distance between NYC to Toronto: " << dist[NYC][Toronto];
	cout << endl << endl;
	return;
}

void LCS(string A, string B){

	//Initialization of making Array
	int row = A.length()+1;
	int col = B.length()+1;
	int table [row][col];
	
	//Making the Array
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			table [i][j] = 0;
		}
	}

	//Make the table and determine the size
	for(int i = 1; i < row; i++){	
		for(int j = 1; j < col; j++){
			if(A[i-1] == B[j-1]){
				table[i][j] = table[i-1][j-1] + 1;
			}
			else{
				table[i][j] = max(table[i-1][j], table[i][j-1]);
			}
		}
	}

	//Check each and put into empty string
	string lcs = "";
	while((row!=0) && (col != 0)){
		if(table[row-1][col-1] == table[row-1][col-2]){
			col--;
		}
		else if(table[row-1][col-1] == table[row-2][col-1]){
			row--;
		}
		else{
			lcs.push_back(A[row-2]);
			row-- ;
			col-- ;
		}
	}

	//Display the results
	cout << "The length of LCS for 2 strings: " << lcs.length() << endl;
	cout << "The Actual String: ";

	//Read back the string to display the answer correctly
	for (int i = lcs.length()-1; i >= 0; i--){
		cout << lcs[i] ;
	}
	cout << endl << endl;
}

void LCS2(string A, string B, string C){

	//Initialization of making Array
	int xLen = A.length()+1;
	int yLen = B.length()+1;
	int zLen = C.length()+1;

	int table [xLen][yLen][zLen];
	
	//Making the Array
	for(int i = 0; i < xLen; i++){
		for(int j = 0; j < yLen; j++){
			for(int k = 0; k < zLen; k++){
				table[i][j][k] = 0;
			}
		}
	}

	//Make the table and determine the size
	for(int i = 1; i < xLen; i++){	
		for(int j = 1; j < yLen; j++){
			for(int k = 1; k < zLen; k++){
				if((A[i-1] == B[j-1]) && (B[j-1] == C[k-1])){
					table[i][j][k] = table[i-1][j-1][k-1] + 1;
				}
				else{
					table[i][j][k] = max2(table[i-1][j][k], table[i][j-1][k], table[i][j][k-1]);
				}
			}
		}
	}

	//Check each and put into empty string
	string lcs2 = "";
	while((zLen!=0) && (yLen != 0) && (xLen !=0)){
		if(table[xLen-1][yLen-1][zLen-1] == table[xLen-1][yLen-1][zLen-2]){
			zLen--;
		}
		else if(table[xLen-1][yLen-1][zLen-1] == table[xLen-1][yLen-2][zLen-1]){
			yLen--;
		}
		else if(table[xLen-1][yLen-1][zLen-1] == table[xLen-2][yLen-1][zLen-1]){
			xLen--;
		}
		else{
			lcs2.push_back(A[xLen-2]);
			zLen--;
			yLen--;
			xLen--;
		}
	}

	//Display the results
	cout << "The length of LCS of 3 strings: " << lcs2.length() << endl;
	cout << "The Actual String: ";

	//Read back the string to display the answer correctly
	for (int i = lcs2.length()-1; i >= 0; i--){
		cout << lcs2[i] ;
	}
	cout << endl << endl;
}

int max(int A, int B){
	return (A > B) ? A:B;
}

int max2(int A, int B, int C){
	int max;

	max = (A > B) ? A:B;

	return(max > C) ? max:C;
}
