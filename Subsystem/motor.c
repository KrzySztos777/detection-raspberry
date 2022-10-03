#include <stddef.h>
#include <stdio.h>
#include "Subsystem.h"
#include "rtwtypes.h"

#include "Subsystem.c"
#include <time.h>
#include <wiringPi.h>
#include <pthread.h> 
#include <signal.h>
#include <stdlib.h>
#include "motorHelpers.c"

//gcc -Wall -o motor.o motor.c -lwiringPi -lpthread -lm

pthread_mutex_t lock;

void *rotationDaemon(void *vargp)
{ 
	struct timespec start, now;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	long long int ticks=0;
	double stepTime=0.0001;
	double diffTime=0.0;
	
	
	while(1){
		
		clock_gettime(CLOCK_MONOTONIC_RAW, &now);
		diffTime = (now.tv_sec+((double)now.tv_nsec)/1000000000) - (start.tv_sec+((double)start.tv_nsec)/1000000000);

		if(diffTime>=(ticks+1)*stepTime){
			ticks++;
			
			pthread_mutex_lock(&lock);
			
			Subsystem_step();
			setStepPin(rtY.stepSignal);
			setDirPin(rtY.dirSignal);
			
			pthread_mutex_unlock(&lock); 
		}
	}
} 

void myExit(int signo)
{
  if (signo == SIGUSR1 || signo==0){
    digitalWrite (ENPIN, HIGH) ;
  }
  
  exit(0);
}

int main(){
	
	wiringPiSetup ();
	setResolution(1,1,0,0);
	Subsystem_initialize();
	
	//starting deamon
	pthread_t tid; 
	pthread_create(&tid, NULL, rotationDaemon, (void *) NULL); 

	//prepare for SIGUSR1
	signal(SIGUSR1, myExit);
	
	//var for holding destinated angle
	double angle=0;
	//var for holding last absolute angle
	double lastAbs=0;

	while(1){
		scanf("%lf",&angle);
		
		pthread_mutex_lock(&lock);
		
		rtU.destAngle=lastAbs+angle;
		//rtU.destAngle=rtY.currentAngle+angle;
		
		lastAbs=rtY.currentAngle;
		
		pthread_mutex_unlock(&lock);
	}
	
	return 0;
}
