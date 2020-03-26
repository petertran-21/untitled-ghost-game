#ifndef DOREMOVEDEVENT_H
#define DOREMOVEDEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "DisplayObjectContainer.h"
#include "DisplayObject.h"

using namespace std;

class DORemovedEvent : public Event {
public:
  DORemovedEvent();
  DORemovedEvent(EventDispatcher* source, DisplayObjectContainer* displayTree, int DTNumChildren, DisplayObject* recentlyRemoved);
  ~DORemovedEvent();
  void checkCondition();

  int DTNumChildren;
  DisplayObjectContainer* displayTree;
  DisplayObject* recentlyRemoved;

  const static string DO_REMOVED;

private:

};

#endif
