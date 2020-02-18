#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Event.h"

Event::Event() {
  this->eventType = "";
  this->source = NULL;
}

Event::Event(string eventType, EventDispatcher* source) {
  this->eventType = eventType;
  this->source = source;
}

Event::~Event() {
  
}

string Event::getType() {
  return this->eventType;
}
EventDispatcher* Event::getSource() {
  return this->source;
}

void Event::checkCondition() {

}
