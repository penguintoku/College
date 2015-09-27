#include <stdlib.h> 
#include <stdio.h>
int main(int argc, char* argv[]){
	int i = 0;
	char buf[116];
	char *ptr;
	long ret = strtol(argv[1], &ptr ,16);
	for(i = 0; i <= 112; i +=4){
		*(long*)&buf[i]= ret;
	}
	puts(buf);
}