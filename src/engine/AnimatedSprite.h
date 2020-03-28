#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <rapidxml-1.13/rapidxml.hpp> //--XML Parser for configuration files
#include <rapidxml-1.13/rapidxml_utils.hpp>

using namespace std;
using namespace rapidxml;

struct Frame {
	SDL_Surface* image;
	SDL_Texture* texture;
};

struct Animation {
	Frame** frames;
	string animName;
	int numFrames;
	int frameRate;
	bool loop;
	int curFrame;
};

struct Layers {
	int x;
	int y;
	int width;
	int height;
};

struct SpriteSheet {
	Layers** layers;
	string spriteSheetPath;
	string animName;
	int numLayers;
	int frameRate;
	int curLayer;
	bool loop;
};

class AnimatedSprite : public Sprite{

public:

	AnimatedSprite();
	AnimatedSprite(string id);
	//AnimatedSprite(string id, string spriteSheetPath, string xmlPath);
	~AnimatedSprite();

	void addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop);
	void addSpriteSheet(string spriteSheetPath, string xmlFilePath, string animName, int numLayers, int frameRate, bool loop);
	Animation* getAnimation(string animName);
	SpriteSheet* getSpriteSheet(string animName);

	void play(string animName);
	void replay();
	void stop();

	virtual void update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState);
	virtual void draw(AffineTransform &at);

	bool playing = false;
	bool playingSheet = false;

private:
	Animation* currentFrames;
	SpriteSheet* currentSpriteSheet;
	vector<Animation*> animations;
	vector<SpriteSheet*> spriteSheets;
	int frameCount = 0;

};

#endif
