#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"

using namespace std;

class EventDispatcher;
class Event {
public:
  Event();
  Event(string eventType, EventDispatcher* source);
  ~Event();

  string getType();
  EventDispatcher* getSource();
  virtual void checkCondition();

private:
  string eventType = "";
  EventDispatcher* source;
};

#endif
