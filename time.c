#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// The program will be invoked with one numeric argument, e.g "./eventsimulator 10"
int main (int argc, char *argv[]) { 


	typedef struct events {
		time_t time;
		char type[9];
		int duration;
	} events;

	struct tm start_time;
	time_t t;
	srand((unsigned) time(&t));
	int temp, i, n;
	char type[2][9]= {"REQUEST", "RESPONSE"};

	sscanf(argv[1], "%d", &n);

	//Creates an array of such structs
	events *event = (events *) calloc (n,sizeof(events));

	if( argc == 2 )
	{
			
			//Populating fake data into such structs 

			
			temp= rand()%115;
			temp+= 1900;

			start_time.tm_year = temp-1900;

			temp= rand()%12+1;
			start_time.tm_mon = temp;

			temp= rand()%31+1;
			start_time.tm_mday = temp;

			temp= rand()%24+1;
			start_time.tm_hour = temp;

			temp= rand()%59+1;
			start_time.tm_min = temp;

			start_time.tm_sec = 0;
			start_time.tm_isdst = 0;

			for(i=0; i<n; i++)
			{
				temp= rand()%59+1;
				start_time.tm_sec += temp;
				event[i].time = mktime(&start_time);
				strcpy(event[i].type, type[rand()%2]);
				event[i].duration= rand()%1000;
			}

			//Print all the events to stdout in format


			for(i=0; i<n; i++)
			{
				printf("%s %d %s\n", "event", i+1, ":");
				printf("\t%s %s %s", "timestamp:", "IST", ctime(&event[i].time));
				printf("\t%s %s\n", "type : ", event[i].type);
				printf("\t%s %d %s\n", "duration : ", event[i].duration, "ms");		
			}
			free(event); 
	   }
	else if( argc > 2 )
	   {
	      printf("Too many arguments supplied.\n");
	   }
	else
	   {
	      printf("One argument expected.\n");
	   }

	return 0;
}


