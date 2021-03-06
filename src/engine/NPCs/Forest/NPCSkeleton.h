#ifndef NPCSKELETON_H
#define NPCSKELETON_H
#define NPCSKELETON_SUBTYPE 29

#include "MainNPC.h"
#include "DisplayObjectContainer.h"

using namespace std;

class NPCSkeleton : public MainNPC{
    
    public:
        NPCSkeleton(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        DisplayObjectContainer* collisionContainer;

        bool alive = false;
        int life_timer = 0;
        int life_timer_max = 30;
};


#endif