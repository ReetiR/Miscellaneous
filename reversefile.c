#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int BUFFER_SIZE = 1;

int main (int argc, char *argv[]) { 
	unsigned char buffer[BUFFER_SIZE];
	FILE *in, *out;
	int i, n, m;
	unsigned int random;
	if( argc == 3 ){
		in = fopen (argv[1], "r");
		out = fopen (argv[2], "w");
		fseek(in, 0, SEEK_END); // seek to end of file
		long size = ftell(in);
		for (i = 0; i < size; i++) { //move back 1 at a time
        	fread(buffer, 1, sizeof(buffer), in); //read 1  byte
	        fwrite(buffer, 1, sizeof(buffer), out); //write 1 byte
    	}
	    fclose(in);
	    fclose(out);
	}
	else if( argc > 3 ){
	      printf("Too many arguments supplied.\n");
	}
	else{
	      printf("Two argument expected.\n");
	}
	return 0;
}