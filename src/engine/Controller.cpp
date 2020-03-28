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

			// CHECK CONTROLLER 0 INPUT
			if (event.jaxis.which == 0) {

				// x-axis of left stick
				if (event.jaxis.axis == 0) {

					// left motion
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
						currState.leftStickX = -1;
					}

					// right motion
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) { 
						currState.leftStickX = 1;
					}

					// no motion
					else {
						currState.leftStickX = 0;
					}
				}

				// y-axis of left stick
				if (event.jaxis.axis == 1) {

					// down motion
					if (event.jaxis.value < -JOYSTICK_DEAD_ZONE) {
						currState.leftStickY = -1;
					}

					// up motion
					else if (event.jaxis.value > JOYSTICK_DEAD_ZONE) {
						currState.leftStickY = 1;
					}

					// no motion
					else {
						currState.leftStickY = 0;
					}
				}
			}

			break;

		case SDL_JOYBUTTONDOWN:

			// CHECK CONTROLLER 0 INPUT
			if (event.jbutton.which == 0) {

				// "A" button pressed
				if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
					currState.buttonA = event.jbutton.state;
				}

				// "X" button pressed
				if (event.jbutton.button == SDL_CONTROLLER_BUTTON_X) {
					currState.buttonX = event.jbutton.state;
				}

				// "Y" button pressed
				if (event.jbutton.button == SDL_CONTROLLER_BUTTON_Y) {
					currState.buttonY = event.jbutton.state;
				}
			}

			break;

		case SDL_JOYBUTTONUP:

			// CHECK CONTROLLER 0 INPUT
			if (event.jbutton.which == 0) {

				// "A" button released
				if (event.jbutton.button == SDL_CONTROLLER_BUTTON_A) {
					currState.buttonA = event.jbutton.state;
				}

				// "X" button released
				if (event.jbutton.button == SDL_CONTROLLER_BUTTON_X) {
					currState.buttonX = event.jbutton.state;
				}

				// "Y" button released
				if (event.jbutton.button == SDL_CONTROLLER_BUTTON_Y) {
					currState.buttonY = event.jbutton.state;
				}
			}

			break;


	}
}

SDL_Joystick* Controller::getJoystick() {
    return joystick;
}

Controller::JoystickState Controller::getJoystickState() {
	return currState;
}