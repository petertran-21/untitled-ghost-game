#ifndef DOADDEDEVENT_H
#define DOADDEDEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "DisplayObject.h"

using namespace std;

class DOAddedEvent : public Event {
public:
  DOAddedEvent();
  DOAddedEvent(EventDispatcher* source, DisplayObject* displayTree);
  ~DOAddedEvent();
  void checkCondition();

  DisplayObject* displayTree;

  const static string DO_ADDED;

private:

};

#endif
