#include <wiringPi.h> //Wiring Pi
#include <softPwm.h> //Servo Motor
#include <stdio.h>
#include <SDL2/SDL.h> //For Sound Library (The core of it)
#include <SDL2/SDL_mixer.h> //For Sound Library (The actual sound stuff we need)

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
#define laserPin 8





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

	//For DC Motor
//	pinMode(MotorPin1, OUTPUT);
//	pinMode(MotorPin2, OUTPUT);
//	pinMode(MotorEnable, OUTPUT);


	//int wingsClosed = 20; //tune to real values later
	//int wingsOpen = 100; //tune to real values later
	//int currentAngle = wingsClosed;

	
//	int cockpitClosed = 0;
//	int cockpitOpen = 70;
//	int currentAngle = cockpitClosed;


	//    Not sure but they had it in the tutorial here
	//    digitalWrite(led1, HIGH);

	softPwmCreate(servoPin, 0, 200);       //initialize PMW pin of servo


	//Initialize the sound libray itself
	if (SDL_Init(SDL_INIT_AUDIO) < 0) { //Check if library sets up right, if not return error
		printf("SDL could not initialize! %s\n", SDL_GetError());
		return 1;
	}

	// Initialize the part of the sound library that plays sounds
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) { //Check if library sets up right, if not return error
		printf("SDL_mixer could not initialize! %s\n", Mix_GetError());
		SDL_Quit();
		return 1;
	}

	// Load WAV file for lazer
	Mix_Chunk *laserSound = Mix_LoadWAV("XWingLazerBeamz.wav");
	if (!laserSound) { //Check if sound is loaded good, if not return error
		printf("Failed to load sound.wav! %s\n", Mix_GetError());
		Mix_CloseAudio();
		SDL_Quit();
		return 1;
	}

	// Load WAV file for flight
	Mix_Chunk *flySound = Mix_LoadWAV("XWingFlyBy.wav");
	if (!flySound) { //Check if sound is loaded good, if not return error
		printf("Failed to load sound.wav! %s\n", Mix_GetError());
		Mix_CloseAudio();
		SDL_Quit();
		return 1;
	}

	//Declare these variables so we make sure the sound doesnt spam
	int lastButtonState = 1;
	int lastTiltState = 1;

	while(1){

		//BUTTON

		//Update button state
		int currentButtonState = digitalRead(button);

		// Indicate that button has pressed down
		if(currentButtonState == 0){
			//Led on
			//digitalWrite(led1, LOW);

			digitalWrite(laserPin, HIGH);
			//play laserSound IFF the lastButton state was off (avoids constant replaying sound and spam and doom)
			if (lastButtonState == 1) {
				//Play laser sound once
				Mix_PlayChannel(-1, laserSound, 0);

			}
			printf("...LED on\n");

		}
		else{
			//Led off
			//digitalWrite(led1, HIGH);
			digitalWrite(laserPin, LOW);

			printf("LED off...\n");
		}
		lastButtonState = currentTiltState;

		//TILT SWITCH + SERVO MOTOR

		int currentTiltState = digitalRead(tilt);

		if(0 == currentTiltState){ //Read of Zero means tilted
			delay(10);
			//setAngle(servoPin,wingsOpen); //sets angle to Open
			printf("Tilt!\n");
			if (lastTiltState == 1) {
				Mix_PlayChannel(-1, flySound, 0);
			
			}

		}
		else if(1 == currentTiltState){ //Read of One means not tilted
			delay(10);
			//setAngle(servoPin,wingsClosed); //sets angle to Closed
			printf("Not Tilting!\n");
		}
		lastTiltState = currentTiltState;

	}



	//Leftover Code from sound testing file
	/*
	// Play sound once
	//Mix_PlayChannel(-1, sound, 0);

	// Wait until the sound finishes
	//SDL_Delay(2000);  // 2000ms = 2 seconds, adjust if sound is longer


	//-1 means use the first free audio channel. Sound is the sound variable we defined before, 0 means only play once
	int channel = Mix_PlayChannel(-1, sound, 0);  // play once


	if (channel == -1) { //make sure it plays at all
	printf("Failed to play sound: %s\n", Mix_GetError()); //error if can't play
	} else {
	while (Mix_Playing(channel) != 0) { //Check if the sound is still playing, if not then end the loop (value is 1 if playing and 0 if not playing)
	SDL_Delay(100);  // wait a short time and check again
	}
	}
	*/


	// Clean up sound library stuff before end program
	Mix_FreeChunk(laserSound);
	Mix_FreeChunk(flySound);
	Mix_CloseAudio();
	SDL_Quit();

	//printf("Sound finished!\n");



	return 0;
}

//-----------------------------------------------------
//DC Motor tutorial code
/*while(1){
        printf("Clockwise\n");
        digitalWrite(MotorEnable, HIGH); //Turns it on
        digitalWrite(MotorPin1, HIGH); //Go clockwise (on)
        digitalWrite(MotorPin2, LOW); // Go counterclockwise (off)
        for(i=0;i<3;i++){
            delay(1000);
        }

        printf("Stop\n");
        digitalWrite(MotorEnable, LOW);
        for(i=0;i<3;i++){
            delay(1000);
        }

        printf("Anti-clockwise\n");
        digitalWrite(MotorEnable, HIGH);
        digitalWrite(MotorPin1, LOW);
        digitalWrite(MotorPin2, HIGH);
        for(i=0;i<3;i++){
            delay(1000);
        }

        printf("Stop\n");
        digitalWrite(MotorEnable, LOW);
        for(i=0;i<3;i++){
            delay(1000);
        }
    }
    return 0;*/
