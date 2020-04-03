#ifndef MAINCOLLECTIBLES_H
#define MAINCOLLECTIBLES_H

#include "AnimatedSprite.h"
#include "Controls.h"
#include "DisplayObjectContainer.h"

using namespace std;

enum class obj_states {Idle};

class MainCollectibles : public AnimatedSprite{
    
    public:
        MainCollectibles();
        MainCollectibles(DisplayObjectContainer* container);
        virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	    virtual void draw(AffineTransform &at);

        obj_states state = obj_states::Idle;
        bool state_new = true;
        bool state_updated = false;

        void state_execute(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_switch(obj_states new_state);
        void state_idle(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
   
};

#endif