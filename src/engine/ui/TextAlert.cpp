#include "UIDefs.h"
#include <iostream>

TextAlert::TextAlert(int posX, int posY, std::string content, DisplayObjectContainer* allSprites) : DisplayObjectContainer(){
    this->text = new Text(content);

    //DisplayObject::loadTexture("./resources/UI_BG.png");
    this->drawingContainer = allSprites;
    allSprites->addChild(this);
    this->addChild(text);
    this->width = 400;
    this->height = 250;
    this->text->reloadFont();
    this->text->width = content.size() * 20;        // Fixes scaling issue.

    this->position.x = posX;
    this->position.y = posY;
}

void TextAlert::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    if (this->text->alpha > 0){
        this->text->position.y -= 1;
        if (this->text->alpha - 4 < 0) this->text->alpha = 0;
        else this->text->alpha -= 4;
    }
    else{
        this->drawingContainer->removeImmediateChild(this);
    }
}