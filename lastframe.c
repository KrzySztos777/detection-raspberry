#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <poll.h>

//This makes read frame always the last one

//COMPILATION:
//gcc lastframe.c -lpthread -o lastframe.o

//USAGE
// ... | lastframe.o 227 227 3 | ...
//then frame is 227(width)x227(height)x3(rgb)

//globals
size_t bufferSize;
pthread_mutex_t lock;
pthread_mutex_t nextFrameLock;
char* buffer;
char* frame;

void *reader(void *vargp){
	size_t readed;
	
	while(1){
		//readed count of bytes is 0
		readed=0;
		
		//reading until buffer is full
		while(readed<bufferSize)
			readed+=fread(buffer+readed,sizeof(*buffer),bufferSize-readed,stdin);
		
		//copying buffer to variable
		pthread_mutex_lock(&lock);
		memcpy(frame,buffer,bufferSize);
		pthread_mutex_unlock(&lock);
		
		//unlocking-new frame is ready
		pthread_mutex_unlock(&nextFrameLock);
		
	}
}

int main(int argc, char *argv[]) {
	
	if(argc==1){
		fprintf(stderr,"Needs more arguments");
		return 1;
	}
	
	//calculationg buffersize
	bufferSize=1;
	for(int i=1;i<argc;i++)
		bufferSize*=atoi(argv[i]);
	
	//preparing buffer and frame
	buffer=malloc(sizeof(*buffer)*bufferSize);
	frame =malloc(sizeof(*buffer)*bufferSize);
	char* currentFrame =malloc(sizeof(*buffer)*bufferSize);
	
	//making deamon which is only reading last frame
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, reader, NULL);
	
	//main loop
	size_t written;
	struct pollfd pfd;
	memset (&pfd, 0, sizeof(pfd));
	pfd.fd=fileno(stdout);
	pfd.events=POLLOUT;
	
	
	while(1){
		//written count of bytes is 0
		written=0;
		//waiting until output wants a data
		poll(&pfd,1,-1);
		
		//copying last frame to variable
		pthread_mutex_lock(&lock);
		memcpy(currentFrame,frame,bufferSize);
		pthread_mutex_unlock(&lock);
		
		//lock- wait for new frame
		pthread_mutex_lock(&nextFrameLock);
		
		//writing last frame to stdout
		while((written+=fwrite(currentFrame+written,sizeof(*frame),bufferSize-written,stdout))<bufferSize)
			;
		
	}
	
}

