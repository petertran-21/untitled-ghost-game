#ifndef DRAGON_H
#define DRAGON_H

#include "MainBoss.h"

using namespace std;

class Dragon : public MainBoss{
    
    public:
        Dragon();
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        int subtype = 5;
   
};


#endif