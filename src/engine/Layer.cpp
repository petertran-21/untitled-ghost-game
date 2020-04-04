#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Layer.h"
#include "DisplayObjectContainer.h"
#include <algorithm>
#include <string>

using namespace std;

Layer::Layer(){
    
}

Layer::Layer(string id, string filepath) : DisplayObjectContainer(id, filepath){
    
}

Layer::~Layer(){}