#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "EventDispatcher.h"

using namespace std;

EventDispatcher::EventDispatcher() {
  listeners = new unordered_map<string, vector<EventListener*>*>();
}

EventDispatcher::~EventDispatcher() {
  this->listeners->clear();
  delete listeners;
}
void EventDispatcher::addEventListener(EventListener* l, string eventType) {
  if (this->listeners->find(eventType) == this->listeners->end()) {
    std::cout << "created new" << std::endl;
    this->listeners->insert( {{ eventType, new vector<EventListener*>() }} );
  }
  (*listeners)[eventType]->push_back(l);
  std::cout << "added" << std::endl;
}
void EventDispatcher::removeEventListener(EventListener* l, string eventType) {
  int i = 0;
  for ( EventListener* listener : *(*listeners)[eventType] ) {
    if(listener == l) {
      (*listeners)[eventType]->erase((*listeners)[eventType]->begin() + i);
      break;
    }
    i++;
  }
}
bool EventDispatcher::hasEventListener(EventListener* l, string eventType) {
  for ( EventListener* listener : *(*listeners)[eventType] ) {
    if(listener == l) {
      return true;
    }
  }
  return false;
}
void EventDispatcher::dispatchEvent(Event* e) {
  for ( EventListener* listener : *(*listeners)[e->getType()] ) {
    listener->handleEvent(e);
  }
}
