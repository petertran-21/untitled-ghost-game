#ifndef NPCSKELETON_H
#define NPCSKELETON_H
#define NPCSKELETON_SUBTYPE 29

#include "MainNPC.h"
#include "DisplayObjectContainer.h"

using namespace std;

class NPCSkeleton : public MainNPC{
    
    public:
        NPCSkeleton(DisplayObjectContainer* container, DisplayObjectContainer* allSprites);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;
        void resolve_collision(DisplayObject *obj);

        bool alive = false;
        int life_timer = 0;
        int life_timer_max = 30;
};


#endif