#include "Scene.h"
#include "AnimatedSprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
// Scene contstructor just calls parent DOC constructor
Scene::Scene() : DisplayObjectContainer(){}

void Scene::loadScene(string sceneFilePath){
    std::ifstream i(sceneFilePath);
    json j = json::parse(i);


    for (auto sprite : j["sprites"]){
        // Get sprite type (static or animated?).
        bool isStatic = (sprite["isStatic"] == true);
        DisplayObjectContainer* unit;
        if (isStatic){
            std::string imgPath = sprite["basePathFolder"].get<std::string>() + sprite["isStaticBaseFile"].get<std::string>();
            unit = new DisplayObjectContainer(sprite["id"].get<std::string>(), imgPath);        // unit->width and unit->height get set here
            unit->width = sprite["width"];
            unit->height = sprite["height"];
        } else {
            unit = new AnimatedSprite();
            for (auto animation : sprite["animationInfo"]["animations"]){
                // thanks David Holmes from Discord - Programming Discussions
                static_cast<AnimatedSprite*>(unit)->addAnimation(sprite["basePathFolder"], animation["animId"], animation["frameCount"], animation["frameRate"], animation["loop"]);
                static_cast<AnimatedSprite*>(unit)->play(animation["animId"]);      // This is just going to end up playing the last listed animation. OK for checkpoint, I guess...
            }
        }
        unit->id = sprite["id"];
        unit->position.x = sprite["posX"];
        unit->position.y = sprite["posY"];
        unit->pivot.x = sprite["pivotX"];
        unit->pivot.y = sprite["pivotY"];
        unit->alpha = sprite["alpha"];
        unit->visible = sprite["isVisible"];
        unit->rotation = sprite["rotation"];
        DisplayObjectContainer::children.push_back(unit);
        this->addChild(unit);
    }
}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}