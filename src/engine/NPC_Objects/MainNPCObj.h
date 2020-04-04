#ifndef MAINNPCOBJ_H
#define MAINNPCOBJ_H

#include "AnimatedSprite.h"
#include "DisplayObjectContainer.h"
#include "Controls.h"

using namespace std;

class MainNPCObj : public AnimatedSprite{
    
    public:
        MainNPCObj();
        MainNPCObj(DisplayObjectContainer* npcParent);
        DisplayObjectContainer* parent;
};
#endif