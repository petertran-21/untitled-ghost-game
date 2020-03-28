#include "TweenEvent.h"

TweenEvent::TweenEvent(std::string eventType, Tween tween){
    this->eventType = eventType;
    this->tween = tween;
}

Tween TweenEvent::getTween(){
    return this->tween;
}