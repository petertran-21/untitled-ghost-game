#include "Scene.h"
#include "AnimatedSprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <iomanip>

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
        } else {
            unit = new AnimatedSprite();
            for (auto animation : sprite["animationInfo"]["animations"]){
                // thanks David Holmes from Discord - Programming Discussions
                static_cast<AnimatedSprite*>(unit)->addAnimation(sprite["basePathFolder"], animation["animId"], animation["frameCount"], animation["frameRate"], animation["loop"]);
                static_cast<AnimatedSprite*>(unit)->play(animation["animId"]);      // This is just going to end up playing the last listed animation. OK for checkpoint, I guess...
            }
            if (sprite["animationInfo"]["playing"]){
                static_cast<AnimatedSprite*>(unit)->playing = true;
            } else {static_cast<AnimatedSprite*>(unit)->playing = false;} // Image wont show up if playing is false.
        }
        unit->id = sprite["id"];
        unit->imgPath = sprite["basePathFolder"];
        unit->position.x = sprite["posX"];
        unit->position.y = sprite["posY"];
        unit->pivot.x = sprite["pivotX"];
        unit->pivot.y = sprite["pivotY"];
        unit->alpha = sprite["alpha"];
        unit->visible = sprite["isVisible"];
        unit->rotation = sprite["rotation"];
        unit->width = sprite["width"];
        unit->height = sprite["height"];
        
        if (sprite["parent"] == "") {
            this->addChild(unit);
        }
    }
}

void Scene::saveScene(string sceneFilePath){
    json j;
    j["sprites"] = {json::array()};
    for (auto sprite : this->children){
        json jsonSprite = {
            {"id", sprite->id},
            {"basePathFolder", sprite->imgPath},
            {"isStatic", true},
            {"posX", sprite->position.x},
            {"posY", sprite->position.y},
            {"pivotX", sprite->pivot.x},
            {"pivotY", sprite->pivot.y},
            {"alpha", sprite->alpha},
            {"isVisible", sprite->visible},
            {"rotation", sprite->rotation},
            {"width", sprite->width},
            {"height", sprite->height}, 
        };

        string parent = "";
        if (sprite->parent != this){
            parent = sprite->parent->id;
        }
        jsonSprite["parent"] = parent;

        if (sprite->type == "AnimatedSprite"){
            jsonSprite["isStatic"] = false;
            jsonSprite["animationInfo"] = {};
            jsonSprite["animationInfo"]["playing"] = static_cast<AnimatedSprite*>(sprite)->playing;
            jsonSprite["animationInfo"]["animations"] = {json::array()};
            
            for (Animation* anim : static_cast<AnimatedSprite*>(sprite)->getAnimations()){
                jsonSprite["animationInfo"]["animations"].push_back({
                    {"animId", anim->animName},
                    {"frameCount", anim->numFrames},
                    {"frameRate", anim->frameRate},
                    {"loop", anim->loop}
                }); 
            }
        } else {
            jsonSprite["isStatic"] = true;
        }
        cout << sprite->id << endl;
        j["sprites"].push_back(jsonSprite);
    }
    
    std::ofstream o(sceneFilePath + ".json");
    o << std::setw(4) << j << std::endl;
}

void Scene::update(set<SDL_Scancode> pressedKeys){
    DisplayObjectContainer::update(pressedKeys);
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}