#ifndef HORNFRAGMENT_H
#define HORNFRAGMENT_H
#define HORNFRAGMENT_SUBTYPE 30

#include "Controller.h"
#include "MainCollectibles.h"
#include "DisplayObjectContainer.h"

using namespace std;

class HornFragment : public MainCollectibles{
    
    public:
        HornFragment(DisplayObjectContainer* container);

};

#endif