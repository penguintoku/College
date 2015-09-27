/**
Read the README before starting!!!!
Tokumaru Yahashi
**/

#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include "time_functions_new.h"

using namespace std;

//headers
void *writer(void *args);
void *reader(void *args);

//The struct of a monitor
struct Monitor{
	int seconds;
	int milliseconds;
	int writerWait;
	bool writerActive;
	pthread_cond_t writeAble;
	pthread_cond_t readAble;
	pthread_mutex_t mutex;
	pthread_mutex_t print;

};

//Each thread will have particular ID with pointing to monitor
struct threadArg{
	int threadID;
	Monitor *monitor;
};

int main(void){

	//There must be 4 writers and 2 readers in the assignment
	pthread_t writers[2];
	pthread_t readers[4];

	//Create a new Monitor with defult state
	threadArg args;
	args.monitor = new Monitor;
	args.monitor->seconds = 0;
	args.monitor->milliseconds = 0;
	args.monitor->writerWait = 0;
	args.monitor->writerActive = false;
	pthread_cond_init(&(args.monitor->writeAble), NULL);
	pthread_cond_init(&(args.monitor->readAble), NULL);
	pthread_mutex_init(&(args.monitor->mutex), NULL);
	pthread_mutex_init(&(args.monitor->print), NULL);

	//Assign each writer and reader to the arguments of the thread
	threadArg *writerThreadArg = new threadArg[2];
	threadArg *reader_args = new threadArg[4];

	//create threads for writer and copy to monitor with unique ID
	for(int x = 0; x < 2; x++){
		writerThreadArg[x].monitor = args.monitor;
		writerThreadArg[x].threadID = x + 1;
		pthread_create(&writers[x], NULL, &writer, &writerThreadArg[x]);
	}

	//create threads for reader and copy to monitor with unique ID
	for(int x = 0; x < 4; x++){
		reader_args[x].monitor = args.monitor;
		reader_args[x].threadID = x + 1;
		pthread_create(&readers[x], NULL, &reader, &reader_args[x]);
	}

	//Join the threads created for writer
	for(int x = 0; x < 2; x++){
		pthread_join(writers[x], NULL);
	}

	//Join the threads created for reader
	for(int x = 0; x < 4; x++){
		pthread_join(readers[x], NULL);
	}
	return EXIT_SUCCESS;
}

//The writer
void *writer(void *args){
	int loop = 0;
	threadArg *currentArg = static_cast<threadArg *>(args);

	//Run the thread 10 times each
	while(loop < 10){

		//lock mutex to prevent interuptions
		pthread_mutex_lock(&(currentArg -> monitor -> mutex));
		while(currentArg -> monitor -> writerActive){
			//check if other write is active; if so, put it in the queue
			currentArg -> monitor -> writerWait++;
			//make it wait for the signal
			pthread_cond_wait(&(currentArg -> monitor -> writeAble), &(currentArg -> monitor -> mutex));
			//no more waiting
			currentArg -> monitor -> writerWait--;
		}

		//change writer to be true since it is no longer waiting --> active
		currentArg -> monitor -> writerActive = true;

		//getting the time
		get_wall_time_ints(&(currentArg -> monitor -> seconds), &(currentArg -> monitor -> milliseconds));

		//To avoid the interupts, make sure to lock mutex for printing
		pthread_mutex_lock(&(currentArg -> monitor -> print));
		//print the data
		cout << "DB value set to: " << currentArg -> monitor -> seconds % 1000 << 
		':' << currentArg -> monitor -> milliseconds << " by writer number: " << currentArg -> threadID << endl;
		//unlock the mutex for printing
		pthread_mutex_unlock(&(currentArg -> monitor -> print));

		//unlock the mutex for writing
		pthread_mutex_unlock(&(currentArg -> monitor -> mutex));

		//change writer to be false since it is waiting --> not active
		currentArg -> monitor -> writerActive = false;

		//No writer in the queue, read the readers
		pthread_cond_signal(&(currentArg -> monitor -> writeAble));
		if(currentArg -> monitor -> writerWait == 0){
			pthread_cond_broadcast(&(currentArg -> monitor -> readAble));
		}
		//Waiting 50ms for the Assignment
		millisleep(50);
		//increment the loop
		loop++;
	}
	pthread_exit(NULL);
}

//The reader
void *reader(void *args){
	int loop = 0;
	threadArg *currentArg = static_cast<threadArg *>(args);

	//Run thread 10 times each
	while(loop < 10){
		//must wait for the writer to finish
		pthread_mutex_lock(&(currentArg -> monitor -> mutex));

		while(currentArg -> monitor -> writerWait > 0){
			//wait until all the writers are done then read
			pthread_cond_wait(&(currentArg -> monitor -> readAble), &(currentArg -> monitor -> mutex));
		}

		//for reader to read, we need to unlock mutex
		pthread_mutex_unlock(&(currentArg -> monitor -> mutex));
		//readers are allowed to continue reading. tell other.
		pthread_cond_broadcast(&(currentArg -> monitor -> readAble));

		//getting the time
		int time1 = currentArg -> monitor -> seconds & 1000;
		int time2 = currentArg -> monitor -> milliseconds;

		//To avoid the interupts, make sure to lock mutex for printing
		pthread_mutex_lock(&(currentArg->monitor->print));
		//print the data
		cout << "DB value read =: " << time1 << ':' << time2 << " by reader number: " << currentArg -> threadID << endl;
		//unlock the mutex for printing
		pthread_mutex_unlock(&(currentArg->monitor->print));

		//check if there is writer waiting since writer has priority
		if(currentArg -> monitor -> writerWait > 0){
			pthread_cond_signal(&(currentArg -> monitor -> writeAble));
		}
		//Waiting 100ms for the Assignment
		millisleep(100);
		//increment the loop
		loop++;
	}
	pthread_exit(NULL);
}