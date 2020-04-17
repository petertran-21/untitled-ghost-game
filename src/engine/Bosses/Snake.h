#ifndef SNAKE_H
#define SNAKE_H

#include "MainBoss.h"

using namespace std;

class Snake : public MainBoss{
    
    public:
        Snake();

        void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        int subtype = 7;
   
};


#endif