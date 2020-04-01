#ifndef SNAKE_H
#define SNAKE_H

#include "MainBoss.h"

using namespace std;

class Snake : public MainBoss{
    
    public:
        Snake();
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif