#include "Controller.h"

/**
 * Author: Bradley Knaysi
 * File: Controller.cpp
 * Created: March 5th, 2020
 */

Controller::Controller() {

	// *** PART OF THE CONTROLLER TUTORIAL ***
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	// Controller must be connected via bluetooth to computer before running ./bin/myGame
	printf("SDL_NumJoysticks() = %d\n", SDL_NumJoysticks());

	// Check for joystick
	if(SDL_NumJoysticks() > 0) {
		printf( "Joystick connected! \n" );

		// Load joystick
		joystick = SDL_JoystickOpen(0);
		if(joystick == NULL) {
			printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
		}
	}
};

Controller::~Controller() {
    joystick = NULL;
};

void Controller::setState(SDL_Event event) {
	switch (event.type) {
		case SDL_JOYAXISMOTION:
			if (event.jaxis.which == 0) {// controller 0
				if (event.jaxis.axis == 0) {// x-axis of left stick
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) { // left motion
						currState.leftStickX = -1;
					}
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) { // right motion
						currState.leftStickX = 1;
					}
					else { // no motion
						currState.leftStickX = 0;
					}
				}
				if (event.jaxis.axis == 1) {// y-axis of left stick
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) { // down motion
						currState.leftStickY = -1;
					}
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) { // up motion
						currState.leftStickY = 1;
					}
					else { // no motion
						currState.leftStickY = 0;
					}
				}
			}
	}
}

SDL_Joystick* Controller::getJoystick() {
    return joystick;
}

Controller::JoystickState Controller::getJoystickState() {
	return currState;
}