#include "UIDefs.h"
#include <iostream>

TextBox::TextBox(int posX, int posY, int width, int height) : DisplayObjectContainer(){
    this->text = new Text();

    DisplayObject::loadTexture("./resources/UI_BG.png");
    this->addChild(text);
    this->position.x = posX;
    this->position.y = posY;
    this->width = width;
    this->height = height;
}

TextBox::TextBox(std::string content, int posX, int posY, int width, int height)  : DisplayObjectContainer(){
    this->text = new Text(content);

    DisplayObject::loadTexture("./resources/UI_BG.png");
    this->addChild(text);
    this->position.x = posX;
    this->position.y = posY;
    this->width = width;
    this->height = height;
}

TextBox::~TextBox(){
    delete this->text;
    delete this;
}

void TextBox::setFont(std::string path){
    this->text->font = TTF_OpenFont(path.c_str(), this->text->fontSize);
    this->text->reloadFont();
}

void TextBox::setFontColor(int r, int g, int b){
    this->text->fontColor.r = r;
    this->text->fontColor.g = g;
    this->text->fontColor.b = b;
    this->text->reloadFont();
}

void TextBox::setFontColor(SDL_Color color){
    this->text->fontColor = color;
    this->text->reloadFont();
}

void TextBox::setFontSize(int sz){
    this->text->fontSize = sz;
    this->text->reloadFont();
}

void TextBox::setText(std::string newText){
    this->text->content = newText;
    this->text->reloadFont();
}

void TextBox::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}