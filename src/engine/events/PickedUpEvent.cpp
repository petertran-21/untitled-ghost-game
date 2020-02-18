#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "PickedUpEvent.h"

const string PickedUpEvent::COIN_PICKED_UP = "COIN_PICKED_UP";

PickedUpEvent::PickedUpEvent() : Event() {
  this->character = NULL;
  this->item = NULL;
}

PickedUpEvent::PickedUpEvent(EventDispatcher* source, DisplayObject* character, DisplayObject* item) : Event(PickedUpEvent::COIN_PICKED_UP, source) {
  this->character = character;
  this->item = item;
}

PickedUpEvent::~PickedUpEvent(){

}

void PickedUpEvent::checkCondition(){
    int xDist = this->item->position.x - this->character->position.x;
    int yDist = this->item->position.y - this->character->position.y;


    if (xDist == 0 && yDist == 0){
        this->getSource()->dispatchEvent(this);
    }
}
