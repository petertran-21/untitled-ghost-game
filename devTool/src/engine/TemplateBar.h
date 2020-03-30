#ifndef TEMPLATEBAR_H
#define TEMPLATEBAR_H

#include "DisplayObjectContainer.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "json.hpp"
#include "Camera.h"
#include <string>

using namespace std;
using json = nlohmann::json;

class TemplateBar : public DisplayObjectContainer{

  public:
    TemplateBar();
    TemplateBar(int red, int green, int blue);
    ~TemplateBar();

    virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer );

    //Load characters
    void loadTemplateBar();

  private:

};

#endif
