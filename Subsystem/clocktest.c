#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void funkcja()
{

}

int main()
{
	struct timespec start, now;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	long int ticks=0;
	double stepTime=0.0005;
	double diffTime;
	
	while(1){
		clock_gettime(CLOCK_MONOTONIC_RAW, &now);
		diffTime = (now.tv_sec+((double)now.tv_nsec)/1000000000) - (start.tv_sec+((double)start.tv_nsec)/1000000000);
		
		if(diffTime>=(ticks+1)*stepTime){
			ticks++;
			printf("%f\n",diffTime);
		}
		
		
	}
}
