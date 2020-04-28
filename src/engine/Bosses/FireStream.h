#ifndef FIRE_STREAM_H
#define FIRE_STREAM_H
#define FIRESTREAM_SUBTYPE 200

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class FireStream : public MainEnvObj{
    
    public:
        FireStream(directions dir, DisplayObjectContainer* container);
        directions dir = None;

};

#endif