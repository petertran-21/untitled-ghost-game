#ifndef TWEENTRANSITIONS_H
#define TWEENTRANSITIONS_H

class TweenTransitions{
public:
    TweenTransitions();
    void applyTransition(double percentDone);
    void easeInOut(double percentDone);
    float easeInOut(float timeElapsed,float startValue , float valueChange, float duration);
};

#endif