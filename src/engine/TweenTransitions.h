#ifndef TWEENTRANSITIONS_H
#define TWEENTRANSITIONS_H

#include "TweenTransitionTypes.h"

class TweenTransitions{
public:
    TweenTransitions();
    TweenTransitions(TweenTransitionTypes type);
    double applyTransition(double percentDone);
    // void easeInOut(double percentDone);
    // float easeInOut(float timeElapsed,float startValue , float valueChange, float duration);
private:
    TweenTransitionTypes type;
};

#endif