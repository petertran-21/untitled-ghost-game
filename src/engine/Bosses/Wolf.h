#ifndef WOLF_H
#define WOLF_H
#define WOLF_SUBTYPE 8

#include "MainBoss.h"
#include "Ghost.h"

using namespace std;

class Wolf : public MainBoss{
    
    public:
        Wolf(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);

        int bark_timer = 0;
        int bark_timer_max = 60;

        virtual void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif