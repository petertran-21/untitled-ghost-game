#ifndef FIRE_H
#define FIRE_H

#include "Controller.h"
#include "AnimatedSprite.h"

using namespace std;

class Fire : public AnimatedSprite{
    
    public:

        Fire(SDL_Point pos);

        virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);

};
#endif