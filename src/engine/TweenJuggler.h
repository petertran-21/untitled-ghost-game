#ifndef TWEENJUGGLER_H
#define TWEENJUGGLER_H

#include "Tween.h"
#include <vector>

class TweenJuggler{

public:
    TweenJuggler();
    void add(Tween* tween);
    void nextFrame();
    static TweenJuggler* getInstance();
private:
    static TweenJuggler* instance;
    std::vector<Tween*> tween_list;
};

#endif