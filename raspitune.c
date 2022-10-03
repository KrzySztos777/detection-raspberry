#include <stdio.h>
#include <stdlib.h>

//DOING: if width%32!=0 and/or height%16!=0 then it fix the image output

//COMPILATION: gcc raspitune.c -o raspitune.o
//USAGE: raspivid -n -fps 90 -w 224 -h 224 -t 0 --raw - -rf rgb -o /dev/null  | ./raspitune 224 224 | python3 ./app.py 224 224

/* main.c */
int main(int argc, char *argv[]) {
	
	if(argc!=3){
		fprintf(stderr,"Needs 2 arguments: width and height");
		return 1;
	}
	
	size_t width=atoi(argv[1]);
	size_t height=atoi(argv[2]);	
	
	size_t raspiWidth=width;
	size_t raspiHeight=height;
	
	if(width%16)
		raspiWidth+=16-width%16;
	if(height%16)
		raspiHeight+=16-height%16;
	
	if(width<=0 || height<=0){
		fprintf(stderr,"Wrong width/height argument- must be values greater than 0");
		return 2;
	}
	
	char frame[raspiWidth*raspiHeight*3];
	int line=0;
	
	//LETS GO!!!!
	while(1){
		for(line=0;line<raspiHeight;line++)
			fread(frame+line*width*3,sizeof(*frame),raspiWidth*3,stdin);
		
		fwrite(frame,sizeof(*frame),width*height*3,stdout);
	}
	
	return 0;
}
