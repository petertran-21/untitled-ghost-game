#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "DORemovedEvent.h"

const string DORemovedEvent::DO_REMOVED = "DO_REMOVED";

DORemovedEvent::DORemovedEvent() : Event() {
  this->displayTree = NULL;
  this->DTNumChildren = 0;
}

DORemovedEvent::DORemovedEvent(EventDispatcher* source, DisplayObjectContainer* displayTree) : Event(DORemovedEvent::DO_REMOVED, source) {
  this->displayTree = displayTree;
  this->DTNumChildren = displayTree->children.size();
}

DORemovedEvent::~DORemovedEvent(){

}

void DORemovedEvent::checkCondition(){
  // check if size of allSprites (displayTree) has decreased
  //TODO: check that it removed
  // cout<<"RUNNING REMOVE EVENT CONDITION"<<endl;
  if (this->DTNumChildren > displayTree->children.size()) {
    this->getSource()->dispatchEvent(this);
    this->DTNumChildren = displayTree->children.size();
  }
}

void DORemovedEvent::removeChildCalled(DisplayObject* childRemoved) {
  this->recentlyRemoved = childRemoved;
}
