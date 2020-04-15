#ifndef WOLF_H
#define WOLF_H

#include "MainBoss.h"

using namespace std;

class Wolf : public MainBoss{
    
    public:
        Wolf();
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        int subtype = 8;
   
};


#endif