#ifndef NPCDOCTOR_H
#define NPCDOCTOR_H
#define NPCDOCTOR_SUBTYPE 27

#include "MainNPC.h"

using namespace std;

class NPCDoctor: public MainNPC{
    
    public:
        NPCDoctor(DisplayObjectContainer* container, DisplayObjectContainer* allSprites, vector<DisplayObject*> &passedInventory);
        void state_ability(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
        void resolve_collision(DisplayObject * obj);
};


#endif