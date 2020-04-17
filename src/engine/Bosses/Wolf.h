#ifndef WOLF_H
#define WOLF_H

#include "MainBoss.h"
#include "Ghost.h"

using namespace std;

class Wolf : public MainBoss{
    
    public:
        Wolf();
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

   
};


#endif