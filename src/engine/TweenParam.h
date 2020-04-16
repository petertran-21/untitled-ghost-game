#ifndef TWEENPARAM_H
#define TWEENPARAM_H

#include "TweenableParams.h"
#include "TweenTransitions.h"
#include "Game.h"           // For access to Game's frameCounter attribute.
#include <iostream>

class TweenParam{
public:
    TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time);
    TweenParam(TweenableParams paramToTween, TweenTransitions transition, double startVal, double endVal, double time);
    TweenableParams getParam();
    double getStartVal();
    double getEndVal();
    double getCurVal();
    void setEndVal(double value);
    double getTweenTime();

private:
    TweenableParams param;
    TweenTransitions transition;
    double startVal;
    double endVal;
    double diff;
    double time;
    int frameCounter;
    int gameStartingFrame;  // To get the actual progress, we'll do Game::frameCounter - gameStartingFrame to get total frames since the start of this tween.
};

#endif