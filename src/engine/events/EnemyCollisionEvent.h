#ifndef ENEMYCOLLISIONEVENT_H
#define ENEMYCOLLISIONEVENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "EventDispatcher.h"
#include "DisplayObject.h"

using namespace std;

class EnemyCollisionEvent : public Event {
public:
  EnemyCollisionEvent();
  EnemyCollisionEvent(EventDispatcher* source, DisplayObject* character, DisplayObject* enemy);
  ~EnemyCollisionEvent();
  void checkCondition();

  DisplayObject* character;
  DisplayObject* enemy;

  const static string TAKE_DAMAGE;

private:

};

#endif
