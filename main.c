#include <wiringPi.h> //Wiring Pi
#include <softPwm.h> //Servo Motor
#include <stdio.h>

//Define the pins we used in terms of wiring pi's language
#define button 0
#define tilt 1
#define led1 2
#define led2 3
#define servoPin 4

//These 3 are if we use DC motor
//#define motorPin1 5
//#define motorPin2 6
//#define motorEnable 7


int main(void){

	// When initialize wiring failed, print message to screen
	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !");
		return 1;
	}

	//Declare pins as input or output
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(button, INPUT);
	pinMode(tilt, INPUT);
	pinMode(button, INPUT);
	pinMode(button, INPUT);

	//    Not sure but they had it in the tutorial here
	//    digitalWrite(led1, HIGH);



	while(1){

	//BUTTON
		// Indicate that button has pressed down
		if(digitalRead(button) == 0){
			// Led on
			digitalWrite(led1, LOW);
			//Can add different functionality here

			//  printf("...LED on\n");
		}
		else{
			// Led off
			digitalWrite(led1, HIGH);
			//Can add different functionality here

			//  printf("LED off...\n");
		}

	//TILT SWITCH
		
		if(0 == digitalRead(TiltPin)){ //Read of Zero means tilted
		    delay(10);
            if(0 == digitalRead(TiltPin)){
                printf("Tilt!\n");
				//Add functionality with motor here
			}
        }
        else if(1 == digitalRead(TiltPin)){ //Read of One means not tilted
            delay(10);
            if(1 == digitalRead(TiltPin)){
                printf("Not Tilting!\n");
				//Add functionality with motor here
            
			}
        }

	}

}
return 0;
}
