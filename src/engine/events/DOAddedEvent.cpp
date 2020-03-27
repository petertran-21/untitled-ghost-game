#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "DOAddedEvent.h"

const string DOAddedEvent::DO_ADDED = "DO_ADDED";

DOAddedEvent::DOAddedEvent() : Event() {
  this->displayTree = NULL;
  this->DTNumChildren = 0;
}

DOAddedEvent::DOAddedEvent(EventDispatcher* source, DisplayObjectContainer* displayTree) : Event(DOAddedEvent::DO_ADDED, source) {
  this->displayTree = displayTree;
  this->DTNumChildren = displayTree->children.size();
}

DOAddedEvent::~DOAddedEvent(){

}

void DOAddedEvent::checkCondition(){
  // check if size of allSprites (displayTree) has increased
  if (this->DTNumChildren < displayTree->children.size()) {
    this->getSource()->dispatchEvent(this);
    this->DTNumChildren = displayTree->children.size();
  }
}

void DOAddedEvent::addChildCalled(DisplayObject* childAdded) {
  this->recentlyAdded = childAdded;
}
