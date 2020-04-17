#ifndef PIRATE_H
#define PIRATE_H

#include "MainBoss.h"
#include "Crab.h"

using namespace std;

class Pirate : public MainBoss{
    
    public:
        Pirate();
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_attack(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

        // DisplayObjectContainer* collisionContainer;
        // DisplayObjectContainer* drawingContainer;
        void resolve_collision(DisplayObject* obj);
   
};


#endif