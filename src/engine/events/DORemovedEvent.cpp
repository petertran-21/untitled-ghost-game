#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "DORemovedEvent.h"

const string DORemovedEvent::DO_REMOVED = "DO_REMOVED";

DORemovedEvent::DORemovedEvent() : Event() {
  this->displayTree = NULL;
  this->DTNumChildren = 0;
  this->recentlyRemoved = NULL;
}

DORemovedEvent::DORemovedEvent(EventDispatcher* source, DisplayObject* displayTree, int DTNumChildren, DisplayObject* recentlyRemoved) : Event(DORemovedEvent::DO_REMOVED, source) {
  this->displayTree = displayTree;
  this->DTNumChildren = displayTree->children.size();
  this->recentlyRemoved = recentlyRemoved;
}

DORemovedEvent::~DORemovedEvent(){

}

void DORemovedEvent::checkCondition(){
  // check if size of allSprites (displayTree) has decreased
  if (this->DTNumChildren > displayTree->children.size()) {
    this->getSource()->dispatchEvent(this);
  }
}
