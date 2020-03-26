#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "DOAddedEvent.h"

const string DOAddedEvent::DO_ADDED = "DO_ADDED";

DOAddedEvent::DOAddedEvent() : Event() {
  this->displayTree = NULL;
  this->DTNumChildren = 0;
  this->recentlyAdded = NULL;
}

DOAddedEvent::DOAddedEvent(EventDispatcher* source, DisplayObject* displayTree, int DTNumChildren, DisplayObject* recentlyAdded) : Event(DOAddedEvent::DO_ADDED, source) {
  this->displayTree = displayTree;
  this->DTNumChildren = displayTree->children.size();
  this->recentlyAdded = recentlyAdded;
}

DOAddedEvent::~DOAddedEvent(){

}

void DOAddedEvent::checkCondition(){
  // check if size of allSprites (displayTree) has increased
  if (this->DTNumChildren < displayTree->children.size()) {
    this->getSource()->dispatchEvent(this);
  }
}
