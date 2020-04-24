#include <iostream>
#include <cstdlib>
#include "Poison.h"
#include <math.h>

using namespace std;

Poison::Poison(SDL_Point pos, int angle, DisplayObjectContainer* container, DisplayObjectContainer* allSprites) : MainNPCObj(){
    this->subtype = POISON_SUBTYPE;
    this->id = "poison";

    this->position = pos;
    this->rotation = angle;

	this->addAnimation("./resources/bosses/", "bark", 1, 1, false);

    this->play("bark");
    this->collisionContainer = container;
    container->addChild(this);
    this->drawingContainer = allSprites;
    drawingContainer->addChild(this);
}

void Poison::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    MainNPCObj::update(pressedKeys, currState);
    position.x += cos(rotation) * movespeed;
    position.y += sin(rotation) * movespeed;
}

void Poison::resolve_collision(DisplayObject* obj){
    MainNPC * npc = dynamic_cast<MainNPC*>(obj);
    if (npc && npc->is_possessed == true){
        npc->reverse_controls = true;
    }
    Ghost * g = dynamic_cast<Ghost*>(obj);
    if (g){
        g->reverse_controls = true;
    }

}