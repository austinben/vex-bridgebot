#pragma config(Sensor, dgtl1,  sonarSensor1,   sensorSONAR_cm)
#pragma config(Sensor, dgtl3,  sonarSensor2,   sensorSONAR_cm)
#pragma config(Sensor, dgtl7,  button1,        sensorTouch)
#pragma config(Motor,  port6,           motor1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           motor2,        tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Ben Austin
ENGR 120 Design Lab
2018/03/05

Milestone 3, Part 3: Wall detection and avoidance.

Robot will avoid walls and collisions based on ultrasonic sensor readings.
*/

// These booleans define when button is pushed or sensor is triggered.
bool button1_pushed = false;

bool sonarOneTrigger = false;
bool sonarTwoTrigger = false;

// Monitors the given input for both sonar sensors. Flags for tripped sensors.
void monitorInput() {
    if(SensorValue(sonarSensor1) < 22) {
        sonarOneTrigger = true;
    }
    else sonarOneTrigger = false;

    if (SensorValue(sonarSensor2) < 22) {
        sonarTwoTrigger = true;
    }
    else sonarTwoTrigger = false;
}


// This function detects when the robot hits a wall using sonar sensors.
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

// The main function calls each function required for the specified behaviour of wall detection in Milestone 3
task main() {
	while(true) {
		monitorInput();
		detectWalls();
	}
}