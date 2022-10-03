
#define DIRPIN 2
#define STEPPIN 0
#define ENPIN 3
#define STBYPIN 1

void setDirPin(int signal){
	static int prevSignal =0;
	
	if(prevSignal!=signal){
		if(signal==0)
			digitalWrite (DIRPIN, LOW) ;
		else
			digitalWrite (DIRPIN, HIGH) ;
			
		prevSignal=signal;
	}
}

void setStepPin(int signal){
	static int prevSignal =0;
	
	if(prevSignal!=signal){
		if(signal==0)
			digitalWrite (STEPPIN, LOW) ;
		else
			digitalWrite (STEPPIN, HIGH) ;
			
		prevSignal=signal;
	}
}

void setResolution(int dir, int step, int m1, int m2){
	
	pinMode (DIRPIN, OUTPUT);
	pinMode (STEPPIN, OUTPUT);
	
	pinMode (ENPIN, OUTPUT);
	pinMode (STBYPIN, OUTPUT);

	//OFF ALL
	digitalWrite (STBYPIN, LOW) ;
	digitalWrite (ENPIN, HIGH) ;
	digitalWrite (DIRPIN, LOW) ;
	digitalWrite (STEPPIN, LOW) ;

	//setting... (STEP=1;DIR=1; =>1/8 step)
	digitalWrite (STEPPIN, step) ;
	digitalWrite (DIRPIN, dir) ;
	usleep(110);

	//ON ALL
	digitalWrite (ENPIN, LOW) ;
	digitalWrite (STBYPIN, HIGH) ;
	usleep(110);
	digitalWrite (STEPPIN, LOW) ;
	digitalWrite (DIRPIN, LOW) ;
}
