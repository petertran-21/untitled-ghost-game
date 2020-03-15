#include "AnimatedSprite.h"
#include "Game.h"
#include <string>
#include <iostream>

using namespace rapidxml;

AnimatedSprite::AnimatedSprite() : Sprite() {
    this->type = "AnimatedSprite";
}

AnimatedSprite::AnimatedSprite(string id) : Sprite(id, 0, 0, 0) {
    this->type = "AnimatedSprite";
}

// AnimatedSprite::AnimatedSprite(string id, string spriteSheetPath, string xmlPath) : Sprite(id, spriteSheetPath) {
//   this->type = "AnimatedSprite";
// }

AnimatedSprite::~AnimatedSprite() {
    for (Animation* an : animations) {
        for (int i = 0; i < an->numFrames; i++) {// this needs to be an iterator loop
            if(an->frames[i]->image != NULL) SDL_FreeSurface(an->frames[i]->image);
	        if(an->frames[i]->texture != NULL) SDL_DestroyTexture(an->frames[i]->texture);
            delete an->frames[i];
        }
        delete an->frames;
        delete an;
    }
}

void AnimatedSprite::addAnimation(string basepath, string animName, int numFrames, int frameRate, bool loop) {
    Animation* anim = new Animation();
    anim->animName = animName;
    anim->numFrames = numFrames;
    anim->frameRate = frameRate;
    anim->loop = loop;
    anim->curFrame = 0;
    anim->frames = new Frame*[numFrames]; // new frame pointer array of size numFrames;
    for (int i = 0; i < numFrames; i++ ) {
        Frame* f = new Frame();
        string path = basepath + animName + "_" + to_string(i+1) + ".png";
        f->image = IMG_Load(path.c_str());
        f->texture = SDL_CreateTextureFromSurface(Game::renderer, f->image);
        anim->frames[i] = f;
    }
    animations.push_back(anim);
}

void AnimatedSprite::addSpriteSheet(string spriteSheetPath, string xmlFilePath, string animName, int numLayers, int frameRate, bool loop) {
    SpriteSheet* sheet = new SpriteSheet();
    sheet->animName = animName;
    sheet->spriteSheetPath = spriteSheetPath;
    sheet->numLayers = numLayers;
    sheet->frameRate = frameRate;
    sheet->loop = loop;
    sheet->curLayer = 0;
    sheet->layers = new Layer*[numLayers];

    file<> xml((xmlFilePath).c_str());
    xml_document<> doc;
    doc.parse<parse_full>(xml.data());
    xml_node<>* rootNode = doc.first_node();

    int i = 0;
    for (xml_node<> * layerNode = rootNode->first_node(); layerNode; layerNode = layerNode->next_sibling()) {
      Layer* l = new Layer();
      xml_attribute<> *attr = layerNode->first_attribute();
      l->x = atoi(attr->value());
      attr = attr->next_attribute();
      l->y = atoi(attr->value());
      attr = attr->next_attribute();
      l->width = atoi(attr->value());
      attr = attr->next_attribute();
      l->height = atoi(attr->value());
      sheet->layers[i] = l;
      i++;
    }
    this->spriteSheets.push_back(sheet);


}

Animation* AnimatedSprite::getAnimation(string animName) {
    if(!animations.empty()) {
      for (int i = 0; i < animations.size(); i++) {
          if (animations[i]->animName == animName) {
              return animations[i];
          }
      }
    }
    return NULL;
}

SpriteSheet* AnimatedSprite::getSpriteSheet(string animName) {
    if (!spriteSheets.empty()) {
      for (int i = 0; i < spriteSheets.size(); i++) {
          if (spriteSheets[i]->animName == animName) {
              return spriteSheets[i];
          }
      }
    }
    return NULL;
}

void AnimatedSprite::play(string animName) {
    if(!animations.empty()) {
      Animation* anim = getAnimation(animName);
      if (anim != NULL) {
          this->currentFrames = anim;
          this->currentFrames->curFrame = 0;
          frameCount = 0;
          playing = true;
          playingSheet = false;
      }
    } else if (!spriteSheets.empty()) {
      SpriteSheet* anim = getSpriteSheet(animName);
      if (anim != NULL) {
          this->currentSpriteSheet = anim;
          this->currentSpriteSheet->curLayer = 0;
          frameCount = 0;
          playingSheet = true;
          playing = false;

          DisplayObject::loadTexture(currentSpriteSheet->spriteSheetPath);
      }
    }
}

void AnimatedSprite::replay() {
    if(!animations.empty()) {
      if (this->currentFrames != NULL) {
          currentFrames->curFrame = 0;
          frameCount = 0;
          playing = true;
          playingSheet = false;
      }
    } else if (!spriteSheets.empty()) {
      if (this->currentSpriteSheet != NULL) {

          frameCount = 0;
          playingSheet = true;
          playing = false;
      }
    }
}

void AnimatedSprite::stop() {
    this->playing = false;
    this->playingSheet = false;
}

void AnimatedSprite::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState) {
    Sprite::update(pressedKeys, currState);
    if (playing) {
      frameCount++;
      if (frameCount % currentFrames->frameRate == 0) {
          // increment local frame counter
          currentFrames->curFrame++;
          // check for array out of bounds
          if (currentFrames->curFrame == currentFrames->numFrames) {
              // reset the animation
              currentFrames->curFrame = 0;
              // check for looping
              if (!currentFrames->loop) {
                  stop();
              }
          }
          DisplayObject::setTexture(currentFrames->frames[currentFrames->curFrame]->texture);
      }
    } else if (playingSheet) {
      frameCount++;
      if (frameCount % currentSpriteSheet->frameRate == 0) {
          // increment local frame counter
          currentSpriteSheet->curLayer++;
          // check for array out of bounds
          if (currentSpriteSheet->curLayer == currentSpriteSheet->numLayers) {
              // reset the animation
              currentSpriteSheet->curLayer = 0;
              // check for looping
              if (!currentSpriteSheet->loop) {
                  stop();
              }
          }
          DisplayObject::setSourceRect(currentSpriteSheet->layers[currentSpriteSheet->curLayer]->x,currentSpriteSheet->layers[currentSpriteSheet->curLayer]->y, currentSpriteSheet->layers[currentSpriteSheet->curLayer]->width, currentSpriteSheet->layers[currentSpriteSheet->curLayer]->height);
      }
    }

}

void AnimatedSprite::draw(AffineTransform &at) {
    Sprite::draw(at);
}
