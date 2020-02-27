#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Sound.h"
#include <string>

using namespace std;

Sound::Sound(){
    if (SDL_Init(SDL_INIT_AUDIO) < 0){
        return;
    }
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
        return;
    }
}

Sound::~Sound(){
    Mix_CloseAudio();
}

void Sound::playSFX(string fullPath){
    Mix_Chunk *wave = Mix_LoadWAV(fullPath.c_str());
    if (wave == NULL){
        return;
    }
    if (Mix_PlayChannel(-1, wave, 0) == -1){
        return;
    }
    // Mix_FreeChunk(wave);         // Having this line prevents audio from playing, but may have memleak if not freeing?
}

void Sound::playMusic(string fullPath){
    Mix_Music *music = Mix_LoadMUS(fullPath.c_str());
    if (music == NULL){
        return;
    }
    if (Mix_PlayMusic(music, -1)){
        return;
    }
    while (Mix_PlayingMusic()){}
    // Mix_FreeMusic(music);         // Haven't tested playMusic function yet, FYI
}
