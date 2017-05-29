#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

void seed_rng(void)
{
    int fp = open("/dev/random", O_RDONLY);
    if (fp == -1) abort();
    unsigned seed;
    unsigned pos = 0;
    while (pos < sizeof(seed)) {
        int amt = read(fp, (char *) &seed + pos, sizeof(seed) - pos);
        if (amt <= 0) abort();
        pos += amt;
    }
    srand(seed);
    close(fp);
}

double square(double b)
{
    double z;
    z = b*b;
    return(z);
}

double calculateEuclideanDistance(double* vector1, double* vector2, int N){
	int i;
	double sum =0.0, temp;
	for (i=0; i<N;i++){
		temp = square(vector1[i]-vector2[i]);
		sum+=temp;
	}
	return sqrt(sum);

}

unsigned int randr(unsigned int min, unsigned int max)
{
	// srand(time(0));
	seed_rng();
    return rand()%((max-min)+1)+min;
}

void fileRead(int m){
	int random;
	FILE *fp;
	char *line = NULL;
	char temp[100];
	char *words;
    size_t len = 0;
    ssize_t read;
    int rows, cols, i, j;
    int ch=0;
  	int lines=0;
  	int white_space=0;
  	double dist;
	fp = fopen("test.txt","r");
	if (fp == NULL)
        exit(EXIT_FAILURE);

    while(!feof(fp))
	{
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
	    lines++;
	  }
	}
	rows = lines+1;
	double **matrix = (double **)malloc(rows * sizeof(double *));
	fseek( fp, 0, SEEK_SET );

	if ((read = getline(&line, &len, fp)) != -1){
		for(i=0; line[i]!='\n'; i++){
			if(line[i]==' ')
        		white_space++;
        }
	}
	cols=white_space+1;
	fseek( fp, 0, SEEK_SET );

	for (i=0; i<rows; i++)
         matrix[i] = (double *)malloc(cols * sizeof(double));
    fseek( fp, 0, SEEK_SET );
    rows= 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        // printf("%s", line);
        cols= 0;
        words = strtok(line, " \n");
        while (words !=NULL)   {
        	// printf("%s\n",words);
        	matrix[rows][cols]= atof(words);
        	cols++;
        	words = strtok(NULL," \n");
          }
         rows++;
    }
    // for (i = 0; i < rows; i++) {
    //     for (j = 0; j < cols; j++) {
    //         printf("%lf\t", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("rows%d\n", rows);
    for (i=0; i<m; i++){
    	random = randr(1,rows);
		printf("%d\n", random);
    }
    dist = calculateEuclideanDistance(matrix[0], matrix[1], cols);
    printf("%lf\n", dist);
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

bool isNumber(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
        return false;
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

int main (int argc, char *argv[]) { 
	int m;
	unsigned int random;
	if( argc == 2 ){
		sscanf(argv[1], "%d", &m);
		if(isNumber(argv[1]))
			fileRead(m);
		else
			printf("Integer values to be parsed");
	}
	else if( argc > 2 ){
	      printf("Too many arguments supplied.\n");
	}
	else{
	      printf("One argument expected.\n");
	}
	return 0;
}