#include "DisplayObject.h"
#include "AffineTransform.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "./rapidxml-1.13/rapidxml.hpp"

#define PI 3.14159265

using namespace rapidxml;

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
	curTexture = NULL;
}

DisplayObject::DisplayObject(string id, string filepath){
	this->id = id;
	this->imgPath = filepath;

	loadTexture(filepath);
}

DisplayObject::DisplayObject(string id, int red, int green, int blue){
	isRGB = true;
	this->id = id;

	this->red = red;
	this->blue = blue;
	this->green = green;

	this->loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject(){
	//TODO: Get this freeing working
	if(image != NULL) SDL_FreeSurface(image);
	if(texture != NULL) SDL_DestroyTexture(texture);
}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	setTexture(texture);
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
	texture = SDL_CreateTextureFromSurface(Game::renderer, image);
	SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
	setTexture(texture);
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->curTexture = t;
}

void DisplayObject::setSourceRect(int x, int y, int width, int height) {
	srcrect = {x, y, width, height};
	sourceIsSet = true;
}

void DisplayObject::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){

}

void DisplayObject::draw(AffineTransform &at){
	if(this->drawBox){
		this->createHitbox();
	}
	applyTransformations(at);

	if(curTexture != NULL && visible) {
		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point corner = {0, 0};

		int w = (int)distance(origin, upperRight);
		int h = (int)distance(upperRight, lowerRight);

		dstrect = { origin.x, origin.y, w, h };

		SDL_RendererFlip flip;
		if (facingRight) {
			flip = SDL_FLIP_NONE;
		}
		else {
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (sourceIsSet) {
			SDL_RenderCopyEx(Game::renderer, curTexture, &srcrect, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
		} else {
			SDL_RenderCopyEx(Game::renderer, curTexture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
		}

	}

	reverseTransformations(at);
}

void DisplayObject::applyTransformations(AffineTransform &at) {
	at.translate(position.x, position.y);
	at.rotate(rotation);
	at.scale(scaleX, scaleY);
	at.translate(-pivot.x, -pivot.y);
}

void DisplayObject::reverseTransformations(AffineTransform &at) {
	at.translate(pivot.x, pivot.y);
	at.scale(1.0/scaleX, 1.0/scaleY);
	at.rotate(-rotation);
	at.translate(-position.x, -position.y);
}

int DisplayObject::getWidth() {
	return this->image->w;
}

int DisplayObject::getHeight() {
	return this->image->h;
}

double DisplayObject::distance(SDL_Point &p1, SDL_Point &p2) {
	return sqrt(((p2.y - p1.y)*(p2.y - p1.y)) + ((p2.x - p1.x)*(p2.x - p1.x)));
}

double DisplayObject::calculateRotation(SDL_Point &origin, SDL_Point &p) {
	double y = p.y - origin.y;
	double x = p.x - origin.x;
	return (atan2(y, x) * 180 / PI);
}

void DisplayObject::drawHitbox(){
	drawBox = true;

}

void DisplayObject::createHitbox(){
	SDL_Point upperLeft = {0, 0};
	SDL_Point upperRight = {this->width, 0};
	SDL_Point lowerRight = {this->width, this->height};
	SDL_Point lowerLeft = {0, this->height};
	SDL_Point corner = {0, 0};

	vector<SDL_Point> hitBoxPoints = this->translateHitbox(upperLeft, upperRight, lowerRight, lowerLeft);
	DisplayObject* hitBox = new DisplayObject(this->id + "HitBox", 200,155,255);

	int w = (int)distance(hitBoxPoints.at(0), hitBoxPoints.at(1));
	int h = (int)distance(hitBoxPoints.at(1), hitBoxPoints.at(2));
	SDL_Rect rect = { hitBoxPoints.at(0).x, hitBoxPoints.at(0).y, w, h};
	SDL_RenderCopyEx(Game::renderer, hitBox->curTexture, NULL, &rect, calculateRotation(hitBoxPoints.at(0), hitBoxPoints.at(1)), &corner, SDL_FLIP_NONE);
}

vector<SDL_Point> DisplayObject::translateHitbox(SDL_Point upperLeft, SDL_Point upperRight, SDL_Point lowerRight, SDL_Point lowerLeft){
	AffineTransform* at = new AffineTransform();
	at = this->getGlobalTransform(at);
	vector<SDL_Point> points = vector<SDL_Point>();
	this->hitbox = vector<SDL_Point>();
	this->hitbox.push_back(at->transformPoint(upperLeft.x, upperLeft.y));
	this->hitbox.push_back(at->transformPoint(upperRight.x, upperRight.y));
	this->hitbox.push_back(at->transformPoint(lowerRight.x, lowerRight.y));
	this->hitbox.push_back(at->transformPoint(lowerLeft.x, lowerLeft.y));
	return this->hitbox;

}

vector<SDL_Point> DisplayObject::getHitbox(){
	return this->hitbox;
}

AffineTransform* DisplayObject::getGlobalTransform(AffineTransform* at){

	if (this->parent != NULL){
		at = this->parent->getGlobalTransform(at);
		at->translate(this->parent->pivot.x, this->parent->pivot.y);
	}

	this->applyTransformations(*at);

	return at;
}
