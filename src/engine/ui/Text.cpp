#include "UIDefs.h"
#include <iostream>

Text::Text() : DisplayObjectContainer(){
    if (TTF_Init() == -1){
        std::cout << "TTF initialization failed." << std::endl;
        return;
    }
    this->font = TTF_OpenFont("./resources/SourceSansPro-Regular.ttf", this->fontSize);
    SDL_Surface* fontSurface = TTF_RenderText_Solid(this->font, content.c_str(), this->fontColor);
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(Game::renderer, fontSurface);
    DisplayObject::setTexture(fontTexture);
}

Text::Text(std::string content) : DisplayObjectContainer(){
    if (TTF_Init() == -1){
        std::cout << "TTF initialization failed." << std::endl;
        return;
    }
    this->content = content;
    font = TTF_OpenFont("./resources/SourceSansPro-Regular.ttf", this->fontSize);
    SDL_Surface* fontSurface = TTF_RenderText_Solid(this->font, content.c_str(), this->fontColor);
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(Game::renderer, fontSurface);
    DisplayObject::setTexture(fontTexture);
}

Text::~Text(){
    TTF_CloseFont(font);
    TTF_Quit();
}

void Text::reloadFont(){
    SDL_Surface* fontSurface = TTF_RenderText_Solid(this->font, content.c_str(), this->fontColor);
    SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(Game::renderer, fontSurface);
    DisplayObject::setTexture(fontTexture);
}

void Text::setColor(SDL_Color color){
    this->fontColor = color;
}

void Text::setColor(int r, int g, int b){
    this->fontColor.r = r;
    this->fontColor.g = g;
    this->fontColor.b = b;
}