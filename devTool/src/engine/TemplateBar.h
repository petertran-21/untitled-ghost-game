#ifndef TEMPLATEBAR_H
#define TEMPLATEBAR_H
#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"

class TemplateBar : public DisplayObjectContainer{

public:
	TemplateBar();
  TemplateBar(string id, int red, int green, int blue);
	~TemplateBar();

  void loadTemplateBar();

private:


};

#endif
