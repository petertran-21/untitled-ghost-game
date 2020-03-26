#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

/**
 * Author: Bradley Knaysi
 * File: Controller.h
 * Created: March 5th, 2020
 */
class Controller {

    public:

        struct JoystickState {
            int leftStickX = 0;
            int leftStickY = 0;
            int buttonA = 0; // currently set to increase scale
            int buttonB = 0; // currently set to decrease scale
        };

        Controller();
        ~Controller();

        void setState(SDL_Event event);
        SDL_Joystick* getJoystick();
        Controller::JoystickState getJoystickState();

    private:

        SDL_Joystick* joystick = NULL;
        const int JOYSTICK_DEAD_ZONE = 8000;
        JoystickState currState;
};

#endif
