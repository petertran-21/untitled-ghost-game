#ifndef SNAKE_H
#define SNAKE_H
#define SNAKE_SUBTYPE 7

#include "MainBoss.h"
#include "Poison.h"

using namespace std;

class Snake : public MainBoss{
    
    public:
        Snake(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);

        int poison_timer = 0;
        int poison_timer_max = 150;
        int poison_angle = 0;

        void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
   
};


#endif