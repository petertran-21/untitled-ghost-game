#include "Sound.h"

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
        Mix_FreeChunk(wave);
        return;
    }
}

void Sound::playMusic(string fullPath){
    this->music = Mix_LoadMUS(fullPath.c_str());
    if (this->music == NULL){
        return;
    }
    if (Mix_PlayMusic(this->music, -1)){
        return;
    }
    //while (Mix_PlayingMusic()){}
    // Mix_FreeMusic(music);         // Haven't tested playMusic function yet, FYI
}

void Sound::stopMusic(){
    if (this->music != NULL) {
        Mix_FreeMusic(this->music);
    }
}
