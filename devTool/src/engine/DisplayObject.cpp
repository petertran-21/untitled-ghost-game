#include "DisplayObject.h"

DisplayObject::DisplayObject(){
	image = NULL;
	texture = NULL;
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

	loadRGBTexture(red, green, blue);
}

DisplayObject::~DisplayObject(){
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);
	image = NULL;
	texture = NULL;
}

void DisplayObject::loadTexture(string filepath){
	image = IMG_Load(filepath.c_str());
}

void DisplayObject::loadRGBTexture(int red, int green, int blue){
	image = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0x000000ff);
	SDL_FillRect(image, NULL, SDL_MapRGB(image->format, red, green, blue));
}

void DisplayObject::setTexture(SDL_Texture* t){
	this->texture = t;
}

void DisplayObject::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer ){

}

void DisplayObject::draw( AffineTransform &at, SDL_Renderer* renderer, Mouse* mouse )
{
	applyTransformations(at);

	/**
	 * IMPORTANT
	 * 
	 * In order to create an SDL_Texture, you need its
	 * renderer at instantiation. Because this is not known
	 * until a DisplayObject is added to a specific window,
	 * we initalize the texture at run-time when it is drawn to
	 * its screen for the first time.
	 * 
	 */
	if( texture == NULL )
	{
		texture = SDL_CreateTextureFromSurface( renderer, image );

		if( isRGB )
		{
			SDL_SetTextureBlendMode( texture, SDL_BLENDMODE_BLEND );
		}
	}

	if(texture != NULL && visible) {
		SDL_Point origin = at.transformPoint(0, 0);
		SDL_Point upperRight = at.transformPoint(width, 0);
		SDL_Point lowerRight = at.transformPoint(width, height);
		SDL_Point corner = {0, 0};

		int w = (int)distance(origin, upperRight);
		int h = (int)distance(upperRight, lowerRight);

		SDL_Rect dstrect = { origin.x, origin.y, w, h };
		SDL_RendererFlip flip;
		if (facingRight) {
			flip = SDL_FLIP_NONE;
		}
		else {
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (selected) {
			DisplayObject* selectBox = new DisplayObject("selectBox",200,155,255);
	    	SDL_RenderCopyEx(renderer, selectBox->texture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
		}

		SDL_SetTextureAlphaMod(texture, alpha);
		SDL_RenderCopyEx(renderer, texture, NULL, &dstrect, calculateRotation(origin, upperRight), &corner, flip);
	}
	reverseTransformations(at);
}

DisplayObject* DisplayObject::copy(){
	DisplayObject* copy = new DisplayObject(to_string(rand()), this->imgPath);
	copy->parent = this->parent;
	copy->pivot = this->pivot;
	copy->position.y = this->position.y;
	copy->position.x = this->position.x;
	copy->width = this->width;
	copy->height = this->height;
	copy->visible = this->visible;
	copy->alpha = this->alpha;
	copy->rotation = this->rotation;
	copy->scaleX = this->scaleX;
	copy->scaleY = this->scaleY;
	copy->facingRight = this->facingRight;
	copy->isRGB = this->isRGB;

	return copy;
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
