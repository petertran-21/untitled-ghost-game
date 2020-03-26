#ifndef DOADDEDEVENT_H
#define DOADDEDEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "Event.h"
#include "DisplayObjectContainer.h"

using namespace std;

class DOAddedEvent : public Event {
public:
  DOAddedEvent();
  DOAddedEvent(EventDispatcher* source, DisplayObjectContainer* displayTree);
  ~DOAddedEvent();
  void checkCondition();

  void addChildCalled(DisplayObject* childAdded);

  int DTNumChildren;
  DisplayObjectContainer* displayTree;
  DisplayObject* recentlyAdded = NULL;

  const static string DO_ADDED;

private:

};

#endif
