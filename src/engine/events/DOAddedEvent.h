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
  DOAddedEvent(EventDispatcher* source, DisplayObject* displayTree, int DTNumChildren, DisplayObject* recentlyAdded);
  ~DOAddedEvent();
  void checkCondition();

  int DTNumChildren;
  DisplayObject* displayTree;
  DisplayObject* recentlyAdded;

  const static string DO_ADDED;

private:

};

#endif
