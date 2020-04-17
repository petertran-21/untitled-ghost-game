#include "Layer.h"

Layer::Layer() : DisplayObjectContainer() {
    
}

Layer::Layer(string id, string filepath) : DisplayObjectContainer(id, filepath){
    
}

Layer::~Layer(){}