#include "TweenParam.h"

TweenParam::TweenParam(TweenableParams paramToTween, double startVal, double endVal, double time){
    this->param = paramToTween;
    this->startVal = startVal;
    this->endVal = endVal;
    this->time = time;
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

void TweenParam::setEndVal(double value){
    this->endVal = value;
}

double TweenParam::getTweenTime(){
    return this->time;
}