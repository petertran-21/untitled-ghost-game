#ifndef PIRATE_H
#define PIRATE_H

#include "MainBoss.h"

using namespace std;

class Pirate : public MainBoss{
    
    public:
        Pirate();
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif