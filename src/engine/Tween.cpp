#include "Tween.h"

Tween::Tween(){}

Tween::Tween(DisplayObjectContainer* object){
    this->object = object;
}

Tween::Tween(DisplayObjectContainer* object, TweenTransitions transition){
    this->object = object;
    this->transition = transition;
}

void Tween::animate(TweenableParams fieldToAnimate, double startVal, double endVal, double time){
    TweenParam new_tween = TweenParam(fieldToAnimate, this->transition, startVal, endVal, time);
    tween_params.push_back(new_tween);
}

void Tween::update(){
    for (TweenParam tp : tween_params){
        double value = tp.getCurVal();      // I consider getCurVal() to be the "update()" function of TweenParam.
        switch(tp.getParam()){
            case TweenableParams::X:
                this->object->position.x = value;
                break;
            case TweenableParams::Y:
                this->object->position.y = value;
                break;
            case TweenableParams::ALPHA:
                this->object->alpha = value;
                break;
            case TweenableParams::SCALE_X:
                this->object->scaleX = value;
                break;
            case TweenableParams::SCALE_Y:
                this->object->scaleY = value;
                break;
            case TweenableParams::ROTATION:
                this->object->rotation = value;
                break;
        }
    }
}

bool Tween::isComplete(){
    for (TweenParam tp : tween_params){
        // For each TweenParam, if our current object's position is not yet reached, return false.
        switch(tp.getParam()){
            case TweenableParams::X:
                if (this->object->position.x != tp.getEndVal()) return false;
                break;
            case TweenableParams::Y:
                if (this->object->position.y != tp.getEndVal()) return false;
                break;
            case TweenableParams::ALPHA:
                if (this->object->alpha != tp.getEndVal()) return false;
                break;
            case TweenableParams::SCALE_X:
                if (this->object->scaleX != tp.getEndVal()) return false;
                break;
            case TweenableParams::SCALE_Y:
                if (this->object->scaleY != tp.getEndVal()) return false;
                break;
            case TweenableParams::ROTATION:
                if (this->object->rotation != tp.getEndVal()) return false;
                break;
        }
    }
    return true;    // Occurs once everything matches.
}

// Set the value of an existing TweenableParam.
void Tween::setValue(TweenableParams param, double value){
    // Find the tween that matches the parameter we want to set.
    for (TweenParam tp: tween_params){
        // Set it.
        if (tp.getParam() == param){
            tp.setEndVal(value);
            return;
        }
    }
    std::cout << "setValue() was unable to find the tween in question." << std::endl;
    return;
}
