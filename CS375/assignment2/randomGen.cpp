#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int main(){ 
	ofstream outfile;
	outfile.open("test.txt");

    //generate 1000 values of 0~500 values into a file.
    for(int index=0; index<1000; index++){

    	outfile << 1 + (rand() % 500) << ' ' << 1 + (rand() % 500) <<' ' <<  1 + (rand() % 500) << endl;
/*
        printf("%d %d %d", 1 + (rand() % 500), 1 + (rand() %500), 1 + (rand() %500));
        printf("\n");
        */
    }
    outfile.close(); 
}