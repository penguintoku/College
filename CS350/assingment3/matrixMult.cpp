/*
Read the README before starting!!!
Tokumaru Yahashi
*/
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <pthread.h>

using namespace std;

int **A, **B, **C;

//Header Function
void *mult(void *p);

//Struct for each Matrix
typedef struct{
	int i;
	int j;
	int k;
} m;

//Where the function will start
int main(){

	//initialization
	int i, j, k;
	string line;
	int x = 0;
	int totalRow = 0;
	int totalCol = 0;
	int all[1000];
	int found = 1;

	//I/O
	char fileName[200];
	ifstream inFile;
	ofstream outFile;

	//Matrix 
	int rowA = 0;
	int colA = 0;
	int rowB = 0;
	int colB = 0;

	//Get user file input
	printf("File Input: ");
	scanf("%s", fileName);

	//open file and check if exists
	inFile.open(fileName);
	if (inFile.fail()){
		printf("File does not exist! \n");
		printf("Quiting. Good Bye! \n");
		exit(0);
	}

	//Make a file that has the mult result
	outFile.open("result.txt");

	//Read the file and find a rule '*'
	while (getline(inFile, line)){
		//If '*' found then found the first matrix
		if(line.at(0) == '*' && found){
			found = 0;
			x = 0;
			A = new int*[totalRow];
			for(i = 0; i < totalRow; i++){
				A[i] = new int[totalCol];
			}
			for(i = 0; i < totalRow; i++){
				for(j = 0; j < totalCol; j++){
					A[i][j] = all[x];
					x++;
				}
			}
			rowA = totalRow;
			colA = totalCol;
			totalRow = 0;
			totalCol = 0;
			x = 0;
		}
		//The second matrix
		else if(!found && (totalRow == colA)){
			x = 0;
			B = new int*[totalRow];
			for(i = 0; i < totalRow; i++){
				B[i] = new int[totalCol];
			}
			for(i = 0; i < totalRow; i++){
				for(j = 0; j < totalCol; j++){
					B[i][j] = all[x];
					x++;
				}
			}
			rowB = totalRow;
			colB = totalCol;
		}
		else{
			totalCol = 0;
			totalRow++;
			for(i = 0; i < (int)line.length(); i++){
				if(isdigit(line.c_str()[i])){
					all[x] = line[i] - 48;
					x++;
					totalCol++;
				}
			}
		}
	}

	//Setting in Array
	C = new int*[rowA];
	for (i = 0; i < rowA; i++){
		C[i] = new int[colB];
	}
	
	//Create Threads to do the multiplication of the cells
	for(i = 0; i < rowA; i++){
		for(j = 0; j < colB; j++){
			for(k = 0; k < colA; k++){
				//make enough space for matrix and save data
				m *data = (m*) malloc(sizeof(m));
				data -> i = i;
				data -> j = j;
				data -> k = k;
				//threads for the assignment
				pthread_t tid;
				pthread_create(&tid, NULL, mult, data);
				pthread_join(tid, NULL);
			}
		}
	}
		
	//Print the matrix to the file and output
	for (i = 0; i < rowA; i++) {
		for (j = 0; j < colB; j++) {
			outFile << C[i][j] << " ";
			printf("%d ", C[i][j]);
		}
		outFile << endl;
		printf("\n");
	}
	//Close the files
	inFile.close();
	outFile.close();
	return NULL;
}

//Mult the matrix and adds the result
void *mult(void *p){
	//initialization
	m *data = (m*) p;
	int result = 0;
	
	//doing multiplication
	result = A[data -> i][data -> k] * B[data -> k][data -> j];
	C[data -> i][data -> j] += result;

	//close thread
	pthread_exit(0);
	return NULL;
}