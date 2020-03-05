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

        Controller();
        ~Controller();

        void setState(SDL_Event event);
        SDL_Joystick* getJoystick();

    private:

        SDL_Joystick* joystick = NULL;
        const int JOYSTICK_DEAD_ZONE = 5000;
};

#endif