#ifndef GEM_H
#define GEM_H
#define GEM_SUBTYPE 100

#include "Controller.h"
#include "MainCollectibles.h"
#include "DisplayObjectContainer.h"

using namespace std;

class Gem : public MainCollectibles{
    
    public:
        Gem(DisplayObjectContainer* container);

};

#endif