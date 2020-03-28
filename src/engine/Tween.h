#ifndef TWEEN_H
#define TWEEN_H

#include "DisplayObject.h"
#include "TweenTransitions.h"
#include "TweenParam.h"
#include <vector>

class Tween{
public:
    Tween();        // so that TweenEvent doesn't make the compiler cry, but I don't think this can be used
    Tween(DisplayObjectContainer* object);
    Tween(DisplayObjectContainer* object, TweenTransitions transition);
    void animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time);

    virtual void update();
    bool isComplete();
    void setValue(TweenableParams param, double value);
private:
    DisplayObject* object;
    TweenTransitions transition;
    std::vector<TweenParam> tween_params;
};

#endif