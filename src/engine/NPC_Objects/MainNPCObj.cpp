#include <iostream>
#include <cstdlib>
#include "MainNPCObj.h"

using namespace std;

MainNPCObj::MainNPCObj() : AnimatedSprite("NPCObj"){
    this->type = "NPCObj";
}

MainNPCObj::MainNPCObj(DisplayObjectContainer* npcParent) : AnimatedSprite("NPCObj"){
    this->type = "NPCObj";
    this->parent = npcParent;
}