#include <iostream>
#include <cstdlib>
#include "MainNPCObj.h"

using namespace std;

MainNPCObj::MainNPCObj() : AnimatedSprite("NPCObj"){
    this->type = "NPCObj";
}

MainNPCObj::MainNPCObj(MainNPC* npcParent) : AnimatedSprite("NPCObj"){
    this->type = "NPCObj";
    this->parent = npcParent;
}