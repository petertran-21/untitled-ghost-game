#ifndef TWEENEVENT_H
#define TWEENEVENT_H

#include "events/Event.h"
#include "Tween.h"
#include <string>

class TweenEvent : public Event{
public:
    TweenEvent(std::string eventType, Tween tween);
    Tween getTween();
private:
    std::string eventType;
    Tween tween;
};

#endif