#ifndef TEMPLATEBAR_H
#define TEMPLATEBAR_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "json.hpp"
#include <string>

using namespace std;
using json = nlohmann::json;

class TemplateBar : public DisplayObjectContainer{

  public:
    TemplateBar();
    TemplateBar(int red, int green, int blue);
    ~TemplateBar();

    //Load characters
    void loadTemplateBar();

  private:

};

#endif
