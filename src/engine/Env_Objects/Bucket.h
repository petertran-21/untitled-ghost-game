#ifndef BUCKET_H
#define BUCKET_H
#define BUCKET_SUBTYPE 305

#include "Controller.h"
#include "MainCollectibles.h"


using namespace std;

class Bucket : public MainCollectibles{
    
    public:
        Bucket(DisplayObjectContainer* container);
};

#endif