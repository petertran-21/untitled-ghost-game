#include "TweenParam.h"
#include <iostream>

TweenParam::TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time){
    this->param = paramToTween;
    this->transition = TweenTransitions();  // Linear interpolation if not included?
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->diff = this->endVal - this->startVal;
    this->gameStartingFrame = Game::frameCounter;
}

TweenParam::TweenParam(TweenableParams paramToTween, TweenTransitions transition, double startVal, double endVal, double time){
    this->param = paramToTween;
    this->transition = transition;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
    this->diff = this->endVal - this->startVal;
    this->gameStartingFrame = Game::frameCounter;
}

TweenableParams TweenParam::getParam(){
    return this->param;
}

double TweenParam::getStartVal(){
    return this->startVal;
}

double TweenParam::getEndVal(){
    return this->endVal;
}

double TweenParam::getCurVal(){
    double progress = this->transition.applyTransition((Game::frameCounter - gameStartingFrame) / time);
    if (progress > 1){progress = 1;}    // debug
    return this->startVal + (progress * this->diff);    // Ex: go from 5->11 linearlly. The difference is 6. At 0.5 progress, 5 + (0.5 * 6) = 8.
}

void TweenParam::setEndVal(double value){
    this->endVal = value;
    this->diff = this->endVal - this->startVal;
    this->gameStartingFrame = Game::frameCounter;
}

double TweenParam::getTweenTime(){
    return this->time;
}