#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "MouseClickEvent.h"

const string MouseClickEvent::TILE_SELECTED = "TILE_SELECTED";

MouseClickEvent::MouseClickEvent() : Event() {
  this->character = NULL;
  this->mouse = NULL;
}

MouseClickEvent::MouseClickEvent(EventDispatcher* source, DisplayObjectContainer* character, Mouse* mouse) : Event(MouseClickEvent::TILE_SELECTED, source) {
  this->character = character;
  this->mouse = mouse;
}

MouseClickEvent::~MouseClickEvent(){

}

void MouseClickEvent::checkCondition(){
  for(DisplayObject* child : character->children) {
    if(child->position.x + character->position.x < mouse->selectBoxX && mouse->selectBoxX < child->position.x + child->width + character->position.x
    && child->position.y + character->position.y < mouse->selectBoxY && mouse->selectBoxY < child->position.y + child->height + character->position.y
    && mouse->selectBoxX2 == mouse->selectBoxX && mouse->selectBoxY2 == mouse->selectBoxY
    && !mouse->leftClick) {
      mouse->selectBoxX = mouse->selectBoxY = -1;
      child->selected = true;
      this->getSource()->dispatchEvent(this);
    } else { child->selected = false; }
  }
}
