#include <stdio.h>
#include <stdlib.h>

void target(){
	printf("Woooo! Pwn3d!\n");
	exit(0);
}

void prompt(){
	char buf[100];

	gets(buf);
	printf("You entered: %s\n", buf);

}

int main(){
	prompt();

	return 0;
}

