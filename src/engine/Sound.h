#ifndef SOUND_H
#define SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

using namespace std;

class Sound{ 

public:
	Sound();
	~Sound();

	void playSFX(string fullPath);
	void playMusic(string fullPath);

private:

	
};

#endif