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

	// TODO
}

SDL_Joystick* Controller::getJoystick() {
    return joystick;
}