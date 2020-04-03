#ifndef MAINNPCOBJ_H
#define MAINNPCOBJ_H

#include "AnimatedSprite.h"
#include "DisplayObjectContainer.h"
#include "Controls.h"
#include "MainNPC.h"

using namespace std;

class MainNPCObj : public AnimatedSprite{
    
    public:
        MainNPCObj();
        MainNPCObj(MainNPC* npcParent);
        MainNPC* parent;
};
#endif