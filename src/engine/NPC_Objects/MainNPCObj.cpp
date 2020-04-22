#include <iostream>
#include <cstdlib>
#include "MainNPCObj.h"

using namespace std;

MainNPCObj::MainNPCObj() : AnimatedSprite("NPCObj"){
    this->type = "NPCObj";
    this->id = "NPCObj";
}

MainNPCObj::MainNPCObj(DisplayObjectContainer* npcParent) : AnimatedSprite("NPCObj"){
    this->type = "NPCObj";
    this->id = "NPCObj";
    this->parent = npcParent;
}