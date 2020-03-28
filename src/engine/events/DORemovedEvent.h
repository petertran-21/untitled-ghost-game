#ifndef DOREMOVEDEVENT_H
#define DOREMOVEDEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "Event.h"
#include "DisplayObjectContainer.h"

using namespace std;

class DORemovedEvent : public Event {
public:
  DORemovedEvent();
  DORemovedEvent(EventDispatcher* source, DisplayObjectContainer* displayTree);
  ~DORemovedEvent();
  void checkCondition();

  void removeChildCalled(DisplayObject* childRemoved);

  int DTNumChildren;
  DisplayObjectContainer* displayTree;
  DisplayObject* recentlyRemoved = NULL;

  const static string DO_REMOVED;

private:

};

#endif
