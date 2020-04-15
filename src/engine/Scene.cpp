#include "Scene.h"
#include "DisplayObjectContainer.h"
#include "EnvObjImports.h"
#include "CollectiblesImports.h"

Scene::Scene() : DisplayObjectContainer()
{
    isActive = true;
}

Scene::~Scene()
{
    isActive = false;
}

// void Scene::loadScene(string sceneFilePath){
//     std::ifstream i(sceneFilePath);
//     json j = json::parse(i);

//     Layer* background = new Layer("background", "");
//     Layer* midground = new Layer("midground", "");
//     Layer* foreground = new Layer("foreground", "");

//     this->addChild(background);
//     this->addChild(midground);
//     this->addChild(foreground);
    
//     for (auto sprite : j["sprites"]){
//         // Get sprite type (static or animated?).
//         bool isStatic = (sprite["isStatic"] == true);
//         DisplayObjectContainer* unit;
//         if (isStatic){
//             std::string imgPath = sprite["basePathFolder"].get<std::string>() + sprite["isStaticBaseFile"].get<std::string>();
//             unit = new DisplayObjectContainer(sprite["id"].get<std::string>(), imgPath);        // unit->width and unit->height get set here
//             unit->width = sprite["width"];
//             unit->height = sprite["height"];
//         } else {
//             unit = new AnimatedSprite();
//             for (auto animation : sprite["animationInfo"]["animations"]){
//                 // thanks David Holmes from Discord - Programming Discussions
//                 static_cast<AnimatedSprite*>(unit)->addAnimation(sprite["basePathFolder"], animation["animId"], animation["frameCount"], animation["frameRate"], animation["loop"]);
//                 static_cast<AnimatedSprite*>(unit)->play(animation["animId"]);      // This is just going to end up playing the last listed animation. OK for checkpoint, I guess...
//             }
//         }
//         unit->id = sprite["id"];
//         unit->position.x = sprite["posX"];
//         unit->position.y = sprite["posY"];
//         unit->pivot.x = sprite["pivotX"];
//         unit->pivot.y = sprite["pivotY"];
//         unit->alpha = sprite["alpha"];
//         unit->visible = sprite["isVisible"];
//         unit->rotation = sprite["rotation"];
//         unit->layer = sprite["layer"];
//         if(unit->layer=="background"){
//             background->addChild(unit);
//         }
//         if(unit->layer=="middleground"){
//             midground->addChild(unit);
//         }
//         if(unit->layer=="foreground"){
//             foreground->addChild(unit);
//         }
//         //DisplayObjectContainer::children.push_back(unit);
//         //this->addChild(unit);
//     }
// }

/*
void Scene::loadScene(string sceneFilePath){
    std::ifstream i(sceneFilePath);
    json j = json::parse(i);
    unordered_map<string, DisplayObjectContainer*> parents = {};
    unordered_map<DisplayObject*, string> needsParent = {};

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
            unit->parent = this;
            //cout << unit->id << endl;
        } else {
            // Need to find parent object
            needsParent[unit] = sprite["parent"];

        }

        parents[unit->id] = unit;
        
    }
    // Setting up parents
    for (auto it : needsParent){
        it.first->parent = parents[it.second];
        //cout << it.first->id << endl;
        //cout << it.second << endl;
        parents[it.second]->addChild(it.first);
    }
}
*/

void Scene::loadScene(string sceneFilePath, DisplayObjectContainer* Collisioncontainer){
    std::ifstream i(sceneFilePath);
    json j = json::parse(i);
    unordered_map<string, DisplayObjectContainer*> parents = {};
    unordered_map<DisplayObject*, string> needsParent = {};

    for (auto sprite : j["sprites"]){
        // Get sprite subtype
        DisplayObjectContainer* unit;
        std::string imgPath = ""; //Cannot declare variables in a switch
        
        switch((int)sprite["subtype"]) {
            case 2: // Sprites (usually tiles)
                imgPath = sprite["basePathFolder"].get<std::string>() + sprite["isStaticBaseFile"].get<std::string>();
                unit = new Sprite(sprite["id"].get<std::string>(), imgPath);
                break;
            case 9: // Item Pouch
                unit = new ItemPouch(Collisioncontainer);
                break;

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
            unit->parent = this;
            //cout << unit->id << endl;
        } else {
            // Need to find parent object
            needsParent[unit] = sprite["parent"];

        }

        parents[unit->id] = unit;
        
    }
    // Setting up parents
    for (auto it : needsParent){
        it.first->parent = parents[it.second];
        //cout << it.first->id << endl;
        //cout << it.second << endl;
        parents[it.second]->addChild(it.first);
    }

}

void Scene::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    DisplayObjectContainer::update(pressedKeys, currState);
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}
