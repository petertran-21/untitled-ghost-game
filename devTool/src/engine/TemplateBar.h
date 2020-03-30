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

    //Load characters
    void loadTemplateBar();

    virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer );

  private:

    void fitToBottom();
    void slideLeft(set<SDL_Scancode> pressedKeys);
    void slideRight(set<SDL_Scancode> pressedKeys);

};

#endif
