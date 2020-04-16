#include "TweenJuggler.h"

TweenJuggler* TweenJuggler::instance = NULL;

TweenJuggler::TweenJuggler(){
    if (instance != NULL) {
        cout << "ERROR: Cannot re-initialize" << endl;
    }
    instance = this;
}

void TweenJuggler::add(Tween* tween){
    tween_list.push_back(tween);
}

TweenJuggler* TweenJuggler::getInstance() {
    return instance;
}

void TweenJuggler::nextFrame(){
    for (int i = 0; i < tween_list.size(); i++){
        tween_list[i]->update();
        if (tween_list[i]->isComplete()){
            // TODO: Cleanup once tween is complete.
        }
    }
}