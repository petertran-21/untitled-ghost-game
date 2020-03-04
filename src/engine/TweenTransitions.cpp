#include "TweenTransitions.h"
#include <cmath>

TweenTransitions::TweenTransitions(){

}

void TweenTransitions::applyTransition(double percentDone){

}

void TweenTransitions::easeInOut(double percentDone){
    /*
        https://vitiy.info/easing-functions-for-your-animations/
        https://github.com/jesusgollonet/ofpennereasing/blob/mas5ter/PennerEasing/Elastic.cpp
    */
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
