#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "WallCollisionEvent.h"

const string WallCollisionEvent::BLOCK_MOVEMENT = "BLOCK_MOVEMENT";

WallCollisionEvent::WallCollisionEvent() : Event() {
  this->character = NULL;
  this->enemy = NULL;
}

WallCollisionEvent::WallCollisionEvent(EventDispatcher* source, DisplayObject* character, DisplayObject* wall) : Event(WallCollisionEvent::BLOCK_MOVEMENT, source) {
  this->character = character;
  this->enemy = wall;
}

WallCollisionEvent::~WallCollisionEvent(){

}

void WallCollisionEvent::checkCondition(){
    int xDist = this->wall->position.x - this->character->position.x;
    int yDist = this->wall->position.y - this->character->position.y;


    if (xDist == 0 && yDist == 0){
        this->getSource()->dispatchEvent(this);
    }
}
