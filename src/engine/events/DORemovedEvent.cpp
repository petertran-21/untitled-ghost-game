#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "DORemovedEvent.h"

const string DORemovedEvent::DO_REMOVED = "DO_REMOVED";

DORemovedEvent::DORemovedEvent() : Event() {
  this->displayTree = NULL;
}

DORemovedEvent::DORemovedEvent(EventDispatcher* source, DisplayObject* displayTree) : Event(DORemovedEvent::DO_REMOVED, source) {
  this->displayTree = displayTree;
}

DORemovedEvent::~DORemovedEvent(){

}

void DORemovedEvent::checkCondition(){

}
