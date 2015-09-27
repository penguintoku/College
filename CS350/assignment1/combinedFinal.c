/**
Please look at README before starting anything!!
Tokumaru Yahashi
**/

#include <stdio.h>
#include <stdlib.h>
#include "time_functions.h"

/**
Only one function which will run, ask user for input file name, 
outputfile name, provide errors if necessary, and copy from 
inputfile to output file. At the end the program will provide the time of execution. 
**/

FILE *finput, *foutput;
void characterByCharacter();
void lineByLine();
void error();

int main(){
	//allocate memory of 100 which should fit all the path if necessary. 
	char fname[100];
	int option;

	//get the user to name input file and open it as read mode
	printf("Enter the input file name: ");
	scanf("%s", fname);
	finput = fopen(fname, "r");

	//display error if file does not exist
	if(finput == NULL){
		printf("ERROR: Unable to find the file\n");
		return 1;
	}

	//If file was found, get user to name output file as write mode
	else{
		printf("File Found.\n");
		printf("Enter the output file name: ");
		scanf("%s", fname);
		foutput = fopen(fname, "w");

		//display error if output file wasn't created
		if (foutput == NULL){
			printf("ERROR: Wasn't able to create output file\n");
			return 1;
		}
		else{
			//Provide the user which option they want to use.
			printf("For character-by-character, press 1.\nFor line-by-line, press 2.\nEnter number: ");
			scanf("%d", &option);
			if(option == 1){
				characterByCharacter();
			}
			else if(option == 2){
				lineByLine();
			}
			else{
				error();
			}
		}
	}
	//closing the input and output files
	fclose(finput);
	fclose(foutput);
	return 0;
}

//For character-by-character
void characterByCharacter(){
	int chara;
	//start the time
	start_timing();
	//reading from the input file character-by-character until the End Of File
	while ((chara = fgetc(finput)) != EOF){
		//To test if really doing character-by-character.
		//printf("This character is: %c\n",chara);
		//writing to the output file character-by-character
		fprintf(foutput, "%c",chara);	
	}
	//stop the time	
	stop_timing();
	//display completed 
	printf("Writing to the output file is complete.\n");
	//display the total times in 10.3f format
	printf("The total 'ftime' time: %10.3f\n", get_wall_clock_diff());
	printf("The total 'getCPUtime' time: %10.3f\n", get_CPU_time_diff());
	printf("Finishing the program!\n");
}

//For line-by-line
void lineByLine(){
	//the lines must be 80 width according to the directions
	char line[80];
	//start the time
	start_timing();
	while (fgets(line, 80, finput) != NULL){
		//To test is really doing line by line.
		//printf("The line is: %s\n",line);
		//writing to the output file line-by-line
		fprintf(foutput, "%s",line);
	}
	//stop the time	
	stop_timing();
	//display completed 
	printf("Writing to the output file is complete.\n");
	//display the total times in 10.3f format
	printf("The total 'ftime' time: %10.3f\n", get_wall_clock_diff());
	printf("The total 'getCPUtime' time: %10.3f\n", get_CPU_time_diff());
	printf("Finishing the program!\n");
}

//Provide error if options are not 1 or 2
void error(){
	printf("WHAT ARE YOU DOING!!! You didn't press 1 or 2!!! The program is quitting!!! GOOD BYE!!!\n");
	exit(0);
}