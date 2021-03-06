#pragma config(Sensor, dgtl10, redLED1,        sensorLEDtoVCC)
#pragma config(Sensor, dgtl11, redLED2,        sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, limitSwitch1,   sensorTouch)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*
Ben Austin
ENGR 120 Design Lab
2018/03/05

Milestone 3, Part 2: Target Detection part 2

Robot will display LED values based on its decision of if it is
in the correct location to commence the cable connection process or not.

LED in Digital Port #9 will illuminate if robot is not in correct position.
LED in Digital port #11 will illuminate if robot is in correct position.
*/

bool limitSwitch1_pushed = false; // Initialization

// States
enum robotState {
	CORRECT_POS = 0,
	INCORRECT_POS,
};

// Reset LED status to off
void resetLightStatus() {
	SensorValue[redLED1] = 0;
	SensorValue[redLED2] = 0;
}

// Checks to see if limit switch has been tripped
void monitorInput() {
  	if(SensorValue(limitSwitch1) && !limitSwitch1_pushed) {
    	limitSwitch1_pushed = true;
  	}
  	else {
  		limitSwitch1_pushed = false;
  	}
}

// Main task
task main() {
    robotState switchState = INCORRECT_POS;
    resetLightStatus();
    while(true) {
        monitorInput();
        switch (switchState) {
            case INCORRECT_POS: // State where robot is not in right position for connection
                SensorValue[redLED1] = 0;
                SensorValue[redLED2] = 1;
                if (limitSwitch1_pushed) {
                    switchState = CORRECT_POS;
                }
            case CORRECT_POS: // State where robot satisfys position for connection.
                SensorValue[redLED1] = 1;
                SensorValue[redLED2] = 0;
                if (limitSwitch1_pushed) {
                    switchState = CORRECT_POS;
                }
                else {
                    switchState = INCORRECT_POS;
                }

				default:
					switchState = INCORRECT_POS;
				// Should never get here s
            }
    }
}
