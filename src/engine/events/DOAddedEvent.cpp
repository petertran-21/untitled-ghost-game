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

  if (this->DTNumChildren > displayTree->children.size()) {
    this->getSource()->dispatchEvent(this);
    this->DTNumChildren = displayTree->children.size();
  }

  for (int i=DTNumChildren; i<displayTree->children.size(); i++){
    this->displayTree->children.at(i) -> createHitbox();
    cout<<"TYPES: "<<this->displayTree->children.at(i)->type << " "<<this->displayTree->children.at(i)->subtype<<endl;
    DisplayObjectContainer* obj = (DisplayObjectContainer*) this->displayTree->children.at(i);
    this->recentlyAdded = this->displayTree->children.at(i);
    this->getSource()->dispatchEvent(this);
    this->DTNumChildren = i+1;
    // cout << this->displayTree->children.at(i)->id << endl;
  }

}

void DOAddedEvent::addChildCalled(DisplayObject* childAdded) {
  this->recentlyAdded = childAdded;
}
