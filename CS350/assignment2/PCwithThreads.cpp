/*
Read the README before starting!
Tokumaru Yahashi
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include "time_functions.h"
#include <cstring>
using namespace std;

//pthread_mutex_t mutex;
sem_t full, empty;

//Buffer of 10 data lines
string buffer[10];

//Head and tail for circular buffer
int head = 0;
int tail = 0;

//I/O files
ifstream inFile;
ofstream outFile;
char inName[128];
char outName[128];

//Headers Functions
void userInput();
void *reader(void *param);
void *writer(void *param); 
int readLine(string line);
int writeLine(string line); 

//Main function
int main(){

	//Initialize
	pthread_t read;
	pthread_t write;

	//Get user inNames (I/O)
	userInput();

	//Start the timer
	start_timing();

	//Start threads
	pthread_create(&read,NULL,&reader,&buffer);
	pthread_create(&write,NULL,&writer,&buffer);

	//Join threads
	pthread_join(read, NULL);
	pthread_join(write, NULL);      

	//Stop the timer
	stop_timing();

	//Display the time result
	printf("get_wall_clock_diff time: %f\n", get_wall_clock_diff());
	printf("get_cpu_time_diff: %f\n",get_CPU_time_diff());

	//Close all files
	inFile.close();
	outFile.close();

	return 0;
}

//Getting I/O
void userInput(){

	//Initialize Full and Empty
	sem_init(&full, 0, 0);
	sem_init(&empty, 0, 10);

	//get user input file
	printf("Name of Input File: ");
	scanf("%s", inName);

	//open file and check if exists
	inFile.open(inName);
	if (inFile.fail()){
		printf("File does not exist!");
		exit(0);
	}

	//get user output file 
	printf("Name of Output File: ");
	scanf("%s", outName);

	//Create output file
	outFile.open(outName);
}

//Reader Thread
void *reader(void *param){
	
	//initialize
	string line;

	//while there is a line in a input file
	while(getline(inFile, line)){

		//signal empty
		sem_wait(&empty);

		//Read the line
		readLine(line);

		//signal Full
		sem_post(&full);
	}

	//signal empty
	sem_wait(&empty);

	//add a signature "EOF" to the head
	buffer[head] = "#EOF#";
	head++;
	head %= 10;

	//signal full
	sem_post(&full);

	return NULL;
}

//Reads the lines in the file
int readLine(string line){
	buffer[head] = line;
	head++;
	head %= 10;
	return 0;
}

//Write Thread
void *writer(void *param){
	
	//initialize
	string line;
	int x = 1;

	//while ture
	while(x){

		//signal full
		sem_wait(&full);

		//write to line and get the value
		x = writeLine(line);

		//signal empty
		sem_post(&empty);
	}
	return NULL;
}

//Remove line from buffer
int writeLine (string line){
	
	//check to see the signature "EOF" 
	if(buffer[tail] != "#EOF#"){
		
		//Remove line
		line = buffer[tail];
		outFile << line << endl;
		tail++;
		tail %= 10;
		return 1;
	}
	else{
		return 0;
	}
}