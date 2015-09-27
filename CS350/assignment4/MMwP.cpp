/*
Read the README before starting!!!
Tokumaru Yahashi
*/
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <sys/shm.h> //shmctl, shmget, shmat
#include <sys/types.h> //shmat
#include <errno.h> //error handling for shmctl
#include <cstring> //for strerror

#define SHMPERM 0600 //shared memory permissions

using namespace std;

//global variable are used since not specified not to use
int **A, **B, **C;
volatile int *D;
int fc;
extern int errno; //reporting addition error messages

//defining a struct for matrix
typedef struct {
	int i;
	int j;
	int k;
} m;

//header
void mult(m *data);

int main(){

	//initialization
	int i, j, k;
	string line;
	int count = 0;
	int all[1000];
	int rowCount = 0;
	int colCount = 0;
	bool firstMatrix = true;

	//matrix 
	int rowA = 0;
	int columnA = 0;
	int rowB = 0;
	int columnB = 0;

	//Initialization for user input
	ifstream inFile;
	ofstream outFile;
	char inName[128];
	char outName[128];

	//Ask user what test file is
	printf("Input file name (or path): ");
	scanf("%s", inName);

	//open file and check if exists
	inFile.open(inName);
	if (inFile.fail()){
		printf("File does not exist! \n");
		printf("Quiting. Good Bye! \n");
		exit(0);
	}

	//ask user what the output file would be and open
	printf("Output file name: ");
	scanf("%s", outName);
	outFile.open(outName);

	//read each line
	while (getline(inFile, line)){
		//read until '*' to indicate first matrix
		if ((line.at(0) == '*') && firstMatrix){
			//change flad --> no longer first matrix for next
			firstMatrix = false;
			count = 0;
			A = new int*[rowCount];
			for(i = 0; i < rowCount; i++){
				A[i] = new int[colCount];
			}
			for(i = 0; i < rowCount; i++){
				for(j = 0; j < colCount; j++){
					A[i][j] = all[count];
					count++;
				}
			}
			rowA = rowCount;
			columnA = colCount;
			rowCount = 0;
			colCount = 0;
			count = 0;
		}
		//seconf matrix
		else if(!firstMatrix && (rowCount == columnA)){
			count = 0;
			B = new int*[rowCount];
			for (i = 0; i < rowCount; i++){
				B[i] = new int[colCount];
			}
			for (i = 0; i < rowCount; i++){
				for (j = 0; j < colCount; j++){
					B[i][j] = all[count];
					count++;
				}
			}
			rowB = rowCount;
			columnB = colCount;
		}
		else{
			colCount = 0;
			rowCount++;
			for(i = 0; i < (signed)line.length(); i++){
				if(isdigit(line.c_str()[i])){
					all[count] = line[i] - 48;
					count++;
					colCount++;
				}
			}
		}
	}

	//setting in array
	C = new int*[rowA];
	for(i = 0; i < rowA; i++){
		C[i] = new int[columnB];
	}

	/*
	Until here was the same as Project 2A
	We need to change to make it threads --> processes
	Not much change is required
	*/

	/*shmget will return the identifier of the shared memory segment
	associated with the value od the argument key.
	
	shmat attaches the shared memory segment identified by shmid 
	to the address space of the calling process.

	IPC_PRIVATE isn't a flag field but a key_t type. 
	If this special value is used for key, the system call 
	ignores everything but the least significant 9 bits of shmflg 
	and creates a new shared memory segment (on success).

	IPC_CREAT to create a new segment. 
	If this flag is not used, then shmget() will find the segment 
	associated with key and check to see if the user has permission 
	to access the segment.

	IPC_EXCL used with IPC_CREAT to ensure failure if the segment 
	already exists.

	Before the shared memory can be used, it must be attached.
	That is, a pointer reference must be acquired in order to use it.
	If the pointers are declared globally, as below, then the parent
	and all spawned processes will inherit these pointers and thus can 
	use the shared memory.
	*/

	//segid: id for shared memory buffer
	int segid = shmget(IPC_PRIVATE, (rowA * columnA * columnB), IPC_CREAT|IPC_EXCL|SHMPERM);
	if (segid == -1){
		printf("ERROR: %s\n", strerror(errno));
		exit(errno);
	}

	//Now all childer can access D
	D = (volatile int*)shmat(segid, 0, 0);    
	fc = -1;

	//Create process to do the multiplication
	pid_t pid;
	for(i = 0; i < rowA; i++){
		for(j = 0; j < columnB; j++){
			for(k = 0; k < columnA; k++){
				m *data = (m*) malloc(sizeof(m));
				data->k = k;
				data->i = i;
				data->j = j;
				fc++;
				//processes for the assignment
				pid = fork();
				if(pid == 0){
					mult(data);
					exit(0);
				}
			}
		}
	}
	for(int i = 0; i < fc; i++){
		waitpid(pid, 0 , 0);
	}

	//Combingine elements for correct results
	int x = 0;
	int total = 0;
	int *E = new int[rowA * columnB];
	for(i = 0; i < (rowA * columnB * columnA); i+=columnA){
		for(j = 0; j < columnA; j++){
			total += D[i + j];
		}
		E[x] = total;
		total = 0;
		x++;
	}

	//Insert to final matix
	int y = 0;
	for (i = 0; i < rowA; i++) {
		for (j = 0; j < columnB; j++) {
			C[i][j] = E[y];
			y++;
		}
	}
                
	//Printing the final result to the file and output
	cout << endl;
	cout << "Final Matrix:" << endl;
	for (i = 0; i < rowA; i++) {
		for (j = 0; j < columnB; j++) {
			outFile << C[i][j] << " ";
			printf("%d ", C[i][j]);
		}
		outFile << endl;
		cout << endl;
	}
	cout << endl;

	/*
	shmctl is the control operation specified by cmd on the shared
	memory segment whose identifier is given in shmid
	*/
	int rc;
	//return shared memory
	if((rc = shmctl(segid, IPC_RMID, NULL)) == -1){
		cout << "ERROR: Shared Memory" << endl;
	}
	
	//Close the files
	inFile.close();
	outFile.close();
	return NULL;
}

//Mult the matix and adds the result
void mult(m *data){

	//Initialization
	int result = 0;

	//Multiplication
	result = A[data->i][data->k] * B[data->k][data->j];
	D[fc] = result;

	return;
}