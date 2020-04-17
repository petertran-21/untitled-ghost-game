#include "TweenTransitions.h"

TweenTransitions::TweenTransitions(){	// If no type set in constructor, use LINEAR by default.
	this->type = TweenTransitionTypes::LINEAR;
}

TweenTransitions::TweenTransitions(TweenTransitionTypes type){
	this->type = type;
}

// Takes in the percent time to completion of a Tween. **ASSUMED RANGE IS FROM 0.0 TO 1.0, WHERE 1.0 REPRESENTS TIME COMPLETION.**
// Returns the percent "progress" of the Tween.
double TweenTransitions::applyTransition(double percentDone){
	// Per slides: TweenTransition should "map the percent time completed on the Tween to the percent of the actual transition that should occur."
	switch (this->type){
		case TweenTransitionTypes::LINEAR:
			return percentDone;				// If we're 0.5 done, return 0.5 on tween completion progress.
		case TweenTransitionTypes::SQRT:
			return pow(percentDone, 0.5);
		case TweenTransitionTypes::QUAD:
			return pow(percentDone, 2.0);	// If we're 0.5 done, return 0.25 on tween completion progress.
		case TweenTransitionTypes::QUINT:
			return pow(percentDone, 5.0);	// If we're 0.5 done, return 0.03125 on tween completion progress.
		default:
			return percentDone;		// By default use linear interpolation.
	}
}

/*
void TweenTransitions::easeInOut(double percentDone){
    // https://vitiy.info/easing-functions-for-your-animations/
    // https://github.com/jesusgollonet/ofpennereasing/blob/mas5ter/PennerEasing/Elastic.cpp
    
}

float TweenTransitions::easeInOut(float timeElapsed,float startValue , float valueChange, float duration) {
	if (timeElapsed==0) 
        return startValue;  
    if ((timeElapsed/=duration/2)==2) 
        return startValue+valueChange; 
	float p=duration*(0.3f*1.5f);
	float a=valueChange; 
	float s=p/4;
	if (timeElapsed < 1) {
		float postFix =a*pow(2,10*(timeElapsed-=1)); 
		return -0.5f*(postFix* sin( (timeElapsed*duration-s)*(2*3.14159)/p )) + startValue;
	} 
	float postFix =  a*pow(2,-10*(timeElapsed-=1)); 
	return postFix * sin( (timeElapsed*duration-s)*(2*3.14159)/p )*0.5f + valueChange + startValue;
}
*/