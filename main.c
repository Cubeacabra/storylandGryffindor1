#include <wiringPi.h> //Wiring Pi
#include <softPwm.h> //Servo Motor
#include <stdio.h>

//Define the pins we used in terms of wiring pi's language
#define button 0
#define tilt 1
#define led1 2
#define led2 3
#define servoPin 4
#define laserPin 8
//These 3 are if we use DC motor
//#define motorPin1 5
//#define motorPin2 6
//#define motorEnable 7


//Function from tutorial that "maps values" in the function after this one?
long Map(long value,long fromLow,long fromHigh,long toLow,long toHigh){
    return (toHigh-toLow)*(value-fromLow) / (fromHigh-fromLow) + toLow;
}

//Function from tutorial that can write to servo angle
void setAngle(int pin, int angle){    //Create a funtion to control the angle of the servo.
    if(angle < 0)
        angle = 0;
    if(angle > 180)
        angle = 180;
    softPwmWrite(pin,Map(angle, 0, 180, 5, 25));
}





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
	pinMode(laserPin, OUTPUT);

	//    Not sure but they had it in the tutorial here
	//    digitalWrite(led1, HIGH);

	softPwmCreate(servoPin, 0, 200);       //initialize PMW pin of servo


	while(1){

	//BUTTON
		// Indicate that button has pressed down
		if(digitalRead(button) == 0){
			// Led on
			//digitalWrite(led1, LOW);
			//Can add different functionality here
			digitalWrite(laser_pin, HIGH);
			//  printf("...LED on\n");
		}
		else{
			// Led off
		//	digitalWrite(led1, HIGH);
			digitalWrite(laser_pin, HIGH);
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

	//SERVO 
		for(i=0;i<181;i++){     // Let servo rotate from 0 to 180.                  
			setAngle(ServoPin,i); //change specifics for our needs
            delay(2);
        }
        delay(1000);
        for(i=181;i>-1;i--){        // Let servo rotate from 180 to 0.              
			setAngle(ServoPin,i); //change specifics for our needs
            delay(2);
        }
        delay(1000);
    }

	}

}
return 0;
}
