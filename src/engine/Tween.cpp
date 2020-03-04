#include "Tween.h"
#include <iostream>

Tween::Tween(){}

Tween::Tween(DisplayObject object){     // By default, linear interpolation?
    this->object = object;
}

Tween::Tween(DisplayObject object, TweenTransitions transition){
    this->object = object;
    this->transition = transition;
}

void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time){
    TweenParam new_tween = TweenParam(fieldToAnimate, startVal, endVal, time);
    tween_params.push_back(new_tween);
}

void Tween::update(){
    for (TweenParam tp : tween_params){
        switch(tp.getParam()){
            case TweenableParams::X:
                std::cout << "X" << std::endl;
                break;
            case TweenableParams::Y:
                std::cout << "Y" << std::endl;
                break;
            case TweenableParams::ALPHA:
                std::cout << "ALPHA" << std::endl;
                break;
            case TweenableParams::SCALE_X:
                std::cout << "SCALE_X" << std::endl;
                break;
            case TweenableParams::SCALE_Y:
                std::cout << "SCALE_Y" << std::endl;
                break;
            case TweenableParams::ROTATION:
                std::cout << "ROTATION" << std::endl;
                break;
        }
    }
}

bool Tween::isComplete(){
    DisplayObject object = this->object;
    for (TweenParam param : tween_params){
        // if object's endVal != param.getEndVal(), return false since something isn't done yet.
    }
    return true;
}

void Tween::setValue(TweenableParams param, double value){
    for (TweenParam tp: tween_params){
        // Find the tween that matches the parameter we want to set.
        if (tp.getParam() == param){
            // Set it.
            tp.setEndVal(value);
            return;
        }
    }
    std::cout << "setValue() was unable to find the tween in question." << std::endl;
    return;
}
