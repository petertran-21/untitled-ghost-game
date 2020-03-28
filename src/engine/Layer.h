#ifndef LAYER_H
#define LAYER_H
#include "DisplayObjectContainer.h"

class Layer : public DisplayObjectContainer{ 

public:
	Layer();
    Layer(string id, string filepath);
	~Layer();
	double speedRate = 1.0;

private:
};

#endif