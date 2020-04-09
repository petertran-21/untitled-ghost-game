#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <set>
#include "AffineTransform.h"
#include "Controller.h"
#include <string>
#include <fstream>
#include <vector>

enum directions {N, S, E, W, None};

using namespace std;

class DisplayObject{

public:
	string id = "DEFAULT_ID";
	string imgPath = "";
	int red, green, blue;
	string type = "DisplayObject";
	string subtype = "";

	DisplayObject* parent = NULL;

	bool isRGB = false;

	DisplayObject();
	DisplayObject(string id, string path);
	DisplayObject(string id, int red, int green, int blue);
	virtual ~DisplayObject();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	void loadTexture(string filepath);
	void loadRGBTexture(int red, int green, int blue);
	void setTexture(SDL_Texture* t);
	void setSourceRect(int x, int y, int width, int height);

	void applyTransformations(AffineTransform &at);
	void reverseTransformations(AffineTransform &at);

	int getWidth();
	int getHeight();

	bool visible = true;
	SDL_Point position = {0, 0};
	int width = 100;
	int height = 100;
	SDL_Point pivot = {0, 0};
	double scaleX = 1.0;
	double scaleY = 1.0;
	double rotation = 0.0; // in radians
	int alpha = 255;
	bool facingRight = true;
	string layer="foreground";
	bool drawBox = false;

	SDL_Surface* image = NULL;
	void drawHitbox();
	void createHitbox();
	virtual void resolve_collision(DisplayObject *obj);
	vector<SDL_Point> translateHitbox(SDL_Point upperLeft, SDL_Point upperRight, SDL_Point lowerRight, SDL_Point lowerLeft);
	vector<SDL_Point> getHitbox();
	AffineTransform* getGlobalTransform(AffineTransform* at);
	SDL_Point lastNonCollidedPos = {0, 0};
	vector<SDL_Point> lastNonCollidedHB;

private:
	double distance(SDL_Point &p1, SDL_Point &p2);
	double calculateRotation(SDL_Point &origin, SDL_Point &p);

	SDL_Texture* texture = NULL;

	/* Texture currently being drawn. Equal to texture for normal DO */
	SDL_Texture* curTexture;

	bool sourceIsSet = false;

	vector<SDL_Point> hitbox;

	SDL_Rect dstrect;
	SDL_Rect srcrect;
};

#endif
