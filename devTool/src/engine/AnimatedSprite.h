#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Sprite.h"
#include "Controller.h"
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

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

class AnimatedSprite : public Sprite{

public:

	AnimatedSprite();
	AnimatedSprite(string id);
	~AnimatedSprite();

	void addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop);
	Animation* getAnimation(string animName);
	vector<Animation*> getAnimations();

	void play(string animName);
	void replay();
	void stop();

	virtual AnimatedSprite* copy();

	virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer );
	virtual void draw( AffineTransform &at, SDL_Renderer* renderer );

	bool playing = false;

private:
	Animation* current;
	vector<Animation*> animations;
	int frameCount;

};

#endif
