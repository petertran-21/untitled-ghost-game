#include "TweenJuggler.h"
#include <iostream>

TweenJuggler::TweenJuggler(){
}

void TweenJuggler::add(Tween tween){
    tween_list.push_back(tween);
}

void TweenJuggler::nextFrame(){
    for (Tween tween : tween_list){
        // TODO: Cleanup if tween is complete
        if (!tween.isComplete()){
            tween.update();
        }
    }
}