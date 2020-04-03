#ifndef ARROW_H
#define ARROW_H

#include "Controller.h"
#include "MainNPCObj.h"

using namespace std;

class Arrow : public MainNPCObj{
    
    public:
        Arrow();
        Arrow(SDL_Point pos, directions direction, MainNPC* npcParent);

        int movespeed = 4;
        directions dir = S;

        int timer = 0;

        void fly();
        virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

};
#endif