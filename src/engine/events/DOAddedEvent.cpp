#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "DOAddedEvent.h"

const string DOAddedEvent::DO_ADDED = "DO_ADDED";

DOAddedEvent::DOAddedEvent() : Event() {
  this->displayTree = NULL;
}

DOAddedEvent::DOAddedEvent(EventDispatcher* source, DisplayObject* displayTree) : Event(DOAddedEvent::DO_ADDED, source) {
  this->displayTree = displayTree;
}

DOAddedEvent::~DOAddedEvent(){

}

void DOAddedEvent::checkCondition(){

}
