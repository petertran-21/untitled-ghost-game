#ifndef BUCKET_H
#define BUCKET_H
#define BUCKET_SUBTYPE 305

#include "Controller.h"
#include "MainEnvObj.h"


using namespace std;

class Bucket : public MainEnvObj{
    
    public:
        Bucket(DisplayObjectContainer* container);
};

#endif