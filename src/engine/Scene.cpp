#include "Scene.h"
#include "DisplayObjectContainer.h"
#include "EnvObjImports.h"
#include "CollectiblesImports.h"
#include "NPCObjImports.h"
#include "NPCImports.h"
#include "Ghost.h"
#include "particle_system/ParticleEmitter.h"
#include "BossImports.h"

Scene::Scene() : DisplayObjectContainer()
{
    isActive = true;
}

Scene::~Scene()
{
    isActive = false;
}

void Scene::loadScene(string sceneFilePath, DisplayObjectContainer* Collisioncontainer){
    this->FilePath = sceneFilePath;
    std::ifstream i(sceneFilePath);
    json j = json::parse(i);
    unordered_map<string, DisplayObjectContainer*> parents = {};
    unordered_map<DisplayObject*, string> needsParent = {};

    DisplayObjectContainer* foreground = new DisplayObjectContainer();
    DisplayObjectContainer* background = new DisplayObjectContainer();
    DisplayObjectContainer* lightEmittingObjects = new DisplayObjectContainer();
    DisplayObjectContainer* lightLayer = new DisplayObjectContainer();
    DisplayObjectContainer* shadowLayer = new DisplayObjectContainer();

    background->parent = this;
    this->addChild(background);

    foreground->parent = this;
    foreground->id = "foreground";
    this->addChild(foreground);

    for (auto sprite : j["sprites"]){
        // Get sprite subtype
        DisplayObjectContainer* unit;
        std::string imgPath = ""; //Cannot declare variables in a switch
        ParticleEmitter* partEmit;

        switch((int)sprite["subtype"]) {
            case SPRITE_SUBTYPE: // Sprites (usually tiles)
                imgPath = sprite["basePathFolder"].get<std::string>() + sprite["isStaticBaseFile"].get<std::string>();
                unit = new Sprite(sprite["id"].get<std::string>(), imgPath);

                if (sprite["isStaticBaseFile"] == "ocean.png") {
                    unit->type = "Wall";
                    Collisioncontainer->addChild(unit);
                }

                break;
            case ITEMPOUCH_SUBTYPE: // Item Pouch
                unit = new ItemPouch(Collisioncontainer);
                break;
            case SHRUB_SUBTYPE:
                unit = new Shrub(Collisioncontainer);
                break;
            case VALVE_SUBTYPE:
                unit = new Valve(Collisioncontainer, E);
                break;
            case CRAB_SUBTYPE:
                unit = new Crab(Collisioncontainer);
                break;
            case NPCPYROMANCER_SUBTYPE:
                unit = new NPCPyromancer(Collisioncontainer, foreground);
                break;
            case NPCOPERATOR_SUBTYPE:
                unit = new NPCOperator(Collisioncontainer, foreground);
                break;
            case NPCEXCAVATOR_SUBTYPE:
                unit = new NPCExcavator(Collisioncontainer, foreground);
                break;
            case NPCCOLLECTOR_SUBTYPE:
                unit = new NPCCollector(Collisioncontainer, foreground);
                break;
            case LOG_SUBTYPE:
                unit = new Log();
                break;
            case BRIDGE_SUBTYPE:
                unit = new Bridge(Collisioncontainer);
                break;
            case GEM_SUBTYPE:
                unit = new Gem(Collisioncontainer);
                break;
            case WOLF_SUBTYPE:
                unit = new Wolf(Collisioncontainer, foreground);
                break;
            case BREAKABLEWALL_SUBTYPE:
                unit = new BreakableWall(Collisioncontainer);
                break;
            /* Looking for...
            Gem Holder
            HornFragment
            */
            case PIRATE_SUBTYPE:
                unit = new Pirate();
                break;
            case WATERJET_SUBTYPE:
                unit = new WaterJet(Collisioncontainer, foreground);
                break;
            case GHOST_SUBTYPE:
                unit = new Ghost();
                partEmit = new ParticleEmitter();
                partEmit->scaleX = 0.25;
                partEmit->scaleY = 0.25;
                unit->addChild(partEmit);
                Collisioncontainer->addChild(unit);  
                break;
            case SCENE_TRIGGER_SUBTYPE:
                unit = new SceneTrigger(Collisioncontainer, sprite["scene_path"]);     
                Collisioncontainer->addChild(unit);        
                break;

        }

        if (unit != NULL) {
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
                background->addChild(unit);
                unit->parent = background;
            }   else if (sprite["parent"] == "foreground") {
                //foreground->addChild(unit);
                //unit->parent = foreground;
                this->addChild(unit);
                unit->parent = this;
                cout << unit->subtype << endl;
            } else {
                // Need to find parent object
                needsParent[unit] = sprite["parent"];

            }
            parents[unit->id] = unit;

        }

    }
    // Setting up parents
    for (auto it : needsParent){
        it.first->parent = parents[it.second];
        //cout << it.first->id << endl;
        //cout << it.second << endl;
        parents[it.second]->addChild(it.first);
    }
    cout << "Scene Loaded" << endl;
}

void Scene::SaveScene(){
    std::ifstream i(this->FilePath);
    json j = json::parse(i);

    // Clear out foreground with exceptions like scene triggers and other objects
    for (int index = 0; index < j["sprites"].size(); index++){
        int subtype = j["sprites"].at(index)["subtype"];
        
        if (subtype != SPRITE_SUBTYPE && subtype != SCENE_TRIGGER_SUBTYPE && subtype != DISPLAYOBJECTCONTAINER_SUBTYPE && subtype != GHOST_SUBTYPE){
            cout << "Save Scene Erasing" << j["sprites"].at(index)["id"] << endl;
            j["sprites"].erase(j["sprites"].begin() + index);
            index--;
        }
    }
    
    // Put in correct foreground objects
    for (int i = 0; i < this->numChildren(); i++) {
        DisplayObject* sprite = this->getChild(i);
        int subtype = sprite->getSubtype();
        if (subtype != SPRITE_SUBTYPE && subtype != SCENE_TRIGGER_SUBTYPE && subtype != DISPLAYOBJECTCONTAINER_SUBTYPE && subtype != GHOST_SUBTYPE) {
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
                {"subtype", sprite->subtype}, 
            };
            string parent = "";
            if (sprite->parent != this){
                parent = sprite->parent->id;
                //cout << parent << endl;
            } else if (sprite->subtype != 2) {
                parent = "foreground";
            }
            
            jsonSprite["parent"] = parent;
            j["sprites"].push_back(jsonSprite);
        }
    }
    
    // Save the scene
    std::ofstream o(this->FilePath);
    o << std::setw(4) << j << std::endl;
}  

void Scene::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState){
    DisplayObjectContainer::update(pressedKeys, currState);
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
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