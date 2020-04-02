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
  for (int i=DTNumChildren; i<displayTree->children.size(); i++){
    cout<< "stats: "<<displayTree->children.size()<<" "<<DTNumChildren<<endl;
    this->displayTree->children.at(i) -> drawHitbox();
    this->displayTree->children.at(i) -> createHitbox();
    DisplayObjectContainer* obj = (DisplayObjectContainer*) this->displayTree->children.at(i);
    this->getSource()->dispatchEvent(this);
    this->DTNumChildren = i;
    this->recentlyAdded = this->displayTree->children.at(i);
  }
  //account for deletion
}

void DOAddedEvent::addChildCalled(DisplayObject* childAdded) {
  this->recentlyAdded = childAdded;
}
