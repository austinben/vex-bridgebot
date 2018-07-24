#pragma config(Sensor, in1,    IR_SCANNER,     sensorReflection)
#pragma config(Sensor, in8,    ,               sensorAnalog)
#pragma config(Sensor, dgtl1,  sonarSensor1,   sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  sonarSensor2,   sensorSONAR_cm)
#pragma config(Sensor, dgtl7,  button1,        sensorTouch)
#pragma config(Sensor, dgtl8,  button2,        sensorTouch)
#pragma config(Sensor, dgtl9,  limitSwitch1,   sensorTouch)
#pragma config(Sensor, dgtl10, redLED1,        sensorLEDtoVCC)
#pragma config(Motor,  port6,           motor1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           motor2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           motor3,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Ben Austin
ENGR 120 Design Lab
2018/03/16

Milestone 4.

Robot is abel to be placed in test arena, then subsequently locate its target.
Uppon arrival at the target, the robot is able to connect a simulated cable.
*/

//Threshhold value for light
const int maxLight = 2000;

// Flags for buttons and sensors ect.
bool button1_pushed = false;
bool button2_pushed = false;
bool limitSwitch1_pushed = false;
bool sonarOneTrigger = false;
bool sonarTwoTrigger = false;
bool allreadyOpen = false;

// Monitors the given input for all sensors and buttons
void monitorInput() {
    if(SensorValue(sonarSensor1) < 10) {
        sonarOneTrigger = true;
    }
    else sonarOneTrigger = false;

    if (SensorValue(sonarSensor2) < 10) {
        sonarTwoTrigger = true;
    }
    else sonarTwoTrigger = false;

	if(SensorValue(limitSwitch1) && !limitSwitch1_pushed) {
    	limitSwitch1_pushed = true;
  	}

	if (SensorValue(button1) && !button1_pushed) {
		button1_pushed = true;
	}

	if (SensorValue(button2) && !button2_pushed) {
		button2_pushed = true;
	}
}

// This function detects when the robot hits a wall using sonar sensors
void detectWalls() {
	if(sonarOneTrigger || sonarTwoTrigger) {
		// Set the drive motors off
		motor[motor1] = 0;
		motor[motor2] = 0;
	}
    else {
        // Robot moves forward
        motor[motor1] = 32;
        motor[motor2] = -30;
    }
}

// This function monitors IR light levels surroudning the robot
bool monitorLight() {
	static int minLevel = 4096;	//Minimum light level seen by sensor
	static int maxLevel = 0; //Maximum light level seen by sensor
	static int diffLevel = 0; //Delta light level seen in last 0.1 seconds

	int lightLevel = SensorValue[IR_SCANNER];
	bool returnValue = false;

	// Check if 100 msecs have elapsed
	if (time1[T1] > 100)  {
	  	// 100 msecs have elapsed.  Compute delta of light level
		diffLevel = maxLevel - minLevel;

		// Reset calculation for next 100 msecs
		maxLevel = 0;
		minLevel = 4096;
		clearTimer(T1);
	}
	else {
	  	// Check for new minimum/maximum light levels
	  	if (lightLevel < minLevel) {
	  		minLevel = lightLevel;
	  	}
	  	else if (lightLevel > maxLevel) {
	  		maxLevel = lightLevel;
	  	}
	}

	// Check if light level difference over threshold
	if (diffLevel > maxLight) {
		returnValue = true;
	}
	else {
		returnValue = false;
	}

	// Returns whether or not IR light level is above the threshold
	return(returnValue);
}

// Stops all movement of robot
void stop() {
	motor[motor1] = 0;
	motor[motor2] = 0;
}

// Releases cable to connect
void connect() {
	motor[motor3] = 20;
	wait1Msec(700);
	motor[motor3] = 0;
	wait1Msec(1000);
	motor[motor1] = -32;
	motor[motor2] = 32;
}

// Main method used to control method calls and robot states
task main() {
 	enum robotState {
	IDLE,
	SCAN,
	FOUND,
	ATTACH,
	};

robotState state = IDLE; // Base state
SensorValue[redLED1] = 0;
while(true) {
	monitorInput();
		switch (state) {
			case IDLE: // Stop all robot movement
				stop();
				monitorInput();
				if (button1_pushed) {
					allreadyOpen = false;
					state = SCAN;
				}
				else {
					state = IDLE;
				}
				break;

			case SCAN: // Robot is actively looking for the beacon
				monitorLight();
				//detectWalls();
				if (monitorLight()) {
					state = FOUND;
				}
				else {
					motor[motor1] = 37.5;
					motor[motor2] = 37.5;
				}
				break;

			case FOUND: // Robot has found the direction of beacon
				motor[motor1] = 24;
				motor[motor2] = -30;
				if (!monitorLight()) {
					state = SCAN;
				}
				if (limitSwitch1_pushed) {
					state = ATTACH;
				}
				break;

			case ATTACH: // Robot satisfys position for connection
				stop();
	            wait1Msec(750);
	            if(!allreadyOpen) {
	            	connect();
	            	wait1Msec(500);
	                SensorValue[redLED1] = 1;
	               	motor[motor1] = -40;
	               	motor[motor2] = 40;
	               	wait1Msec(1000);
	        	}
	            allreadyOpen = true;
	            if (limitSwitch1_pushed) {
	               	state = ATTACH;
	            }
	            else {
	               	state = IDLE;
	            }
	        break;

			default:
				state = IDLE;
				// Should never get here
	  	}
	}
}
