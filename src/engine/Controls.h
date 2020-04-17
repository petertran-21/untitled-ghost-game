#ifndef CONTROLS_H
#define CONTROLS_H

#include <SDL2/SDL.h>
#include <cstdlib>
#include <set>
#include "Controller.h"

using namespace std;

class Controls{

public:
    Controls();
    static bool holdRight(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
    static bool holdLeft(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
    static bool holdUp(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
    static bool holdDown(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

    static bool pressPossess(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
    static bool pressBoo(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
    static bool pressAbility(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
    
    static bool reverse_controls(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

    static bool pressing_possess;
    static bool pressing_boo;
    static bool pressing_ability;

   
};

#endif