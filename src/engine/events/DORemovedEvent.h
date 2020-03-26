#ifndef DOREMOVEDEVENT_H
#define DOREMOVEDEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "DisplayObject.h"

using namespace std;

class DORemovedEvent : public Event {
public:
  DORemovedEvent();
  DORemovedEvent(EventDispatcher* source, DisplayObject* displayTree);
  ~DORemovedEvent();
  void checkCondition();

  DisplayObject* displayTree;

  const static string DO_REMOVED;

private:

};

#endif
