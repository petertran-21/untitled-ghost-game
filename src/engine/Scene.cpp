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
    this->addChild(foreground);

    vector<DisplayObject*> pairedItems;
    for (auto sprite : j["sprites"]){
        // Get sprite subtype
        DisplayObjectContainer* unit;
        std::string imgPath = ""; //Cannot declare variables in a switch
        ParticleEmitter* partEmit;

        switch((int)sprite["subtype"]) {
            case SPRITE_SUBTYPE: // Sprites (usually tiles)
                imgPath = sprite["basePathFolder"].get<std::string>() + sprite["isStaticBaseFile"].get<std::string>();
                unit = new Sprite(sprite["id"].get<std::string>(), imgPath);

                if (sprite["isStaticBaseFile"] == "ocean.png" ||
                    sprite["isStaticBaseFile"] == "water.png" ||
                    sprite["isStaticBaseFile"] == "caveWall.png" ||
                    sprite["isStaticBaseFile"] == "treeTop.png"
                ){
                    unit->type = "Wall";
                    Collisioncontainer->addChild(unit);
                }

                break;
            /*--------------------------Collectibles--------------------------*/
            case ITEMPOUCH_SUBTYPE: // Item Pouch
                unit = new ItemPouch(Collisioncontainer);
                cout<<"foreground address: "<<foreground<<endl;
                cout<<"SPRIET PARENT: "<<sprite["parent"]<<endl;
                break;
            case GEM_SUBTYPE:
                unit = new Gem(Collisioncontainer);
                break;
            /*--------------------------Forest--------------------------*/
            case SHRUB_SUBTYPE:
                unit = new Shrub(Collisioncontainer);
                break;
            case LOG_SUBTYPE:
                unit = new Log(Collisioncontainer);
                break;
            case BRIDGE_SUBTYPE:
                unit = new Bridge(Collisioncontainer);
                break;
            case WOLF_SUBTYPE:
                unit = new Wolf(Collisioncontainer, foreground);
                break;
            case NPCPYROMANCER_SUBTYPE:
                unit = new NPCPyromancer(Collisioncontainer, foreground);
                break;
            case NPCLUMBERJACK_SUBTYPE:
                unit = new NPCLumberjack(Collisioncontainer, foreground);
                break;
            case NPCARCHER_SUBTYPE:
                unit = new NPCArcher(Collisioncontainer, foreground);
                break;
            case NPCSKELETON_SUBTYPE:
                unit = new NPCSkeleton(Collisioncontainer, foreground);
                break;
            /*--------------------------Beach--------------------------*/
            case VALVE_SUBTYPE:
                cout<<"VALVE WAS MADE"<<endl;
                unit = new Valve(Collisioncontainer, E);
                break;
            case BUTTON_SUBTYPE:
                unit = new Button(Collisioncontainer);
                break;
            case DOOR_SUBTYPE:
                unit = new Door(Collisioncontainer, background);
                pairedItems.push_back(unit);
                break;
            case PIT_SUBTYPE:
                unit = new Pit(Collisioncontainer);
                break;
            case CRAB_SUBTYPE:
                unit = new Crab(Collisioncontainer, sprite["posX"], sprite["posY"]);
                break;
            case BREAKABLEWALL_SUBTYPE:
                unit = new BreakableWall(Collisioncontainer);
                break;
            case WATERJET_SUBTYPE:
                unit = new WaterJet(Collisioncontainer, foreground);
                pairedItems.push_back(unit);
                break;
            case NPCOPERATOR_SUBTYPE:
                unit = new NPCOperator(Collisioncontainer, foreground);
                break;
            case NPCEXCAVATOR_SUBTYPE:
                unit = new NPCExcavator(Collisioncontainer, foreground);
                cout<<"foreground exc address: "<<foreground<<endl;
                break;
            case NPCCOLLECTOR_SUBTYPE:
                unit = new NPCCollector(Collisioncontainer, foreground);
                break;
            case PIRATE_SUBTYPE:
                unit = new Pirate();
                break;
            /*--------------------------Universal--------------------------*/
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
            unit->id = (string) sprite["id"];
            cout<<"PLS "<<unit->id<<endl;
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
            unit->subtype = sprite["subtype"];

            if (sprite["parent"] == "") {
                background->addChild(unit);
                unit->parent = background;
            }   else if (sprite["parent"] == "foreground") {
                foreground->addChild(unit);
                unit->parent = foreground;
                // this->addChild(unit);
                // unit->parent = this;
                // cout << unit->subtype << endl;
            } else {
                // Need to find parent object
                needsParent[unit] = sprite["parent"];

            }
            parents[unit->id] = unit;

        }
    }
    cout<<"NUM IN PAIRED ITEMS: "<<pairedItems.size()<<endl;
    for (DisplayObject* child: pairedItems){
        string childID = child->id;
        if (childID.find("Door") != std::string::npos){
            // cout<<"THIS: "<<childID<<endl;
            for (DisplayObject* obj: background->children){
                string objID = obj->id;
                // cout<<"THAT: "<<objID<<endl;
                if (obj->getSubtype()==104 && (objID.back() == childID.back())){
                    cout<<"RUNNING THROUGH THIS: "<<childID<<" "<<objID<<endl;
                    Button* button = (Button*) obj;
                    Door* door = (Door*) child;
                    button->add_door(door);
                    door->parent = button;
                    cout<<"BUTTON SIZE NOW: "<<button->children.size()<<endl;
                }
            }
            //remove door from background container
            vector<DisplayObject*>::iterator itr = find(background->children.begin(), background->children.end(), child);
            if (itr != background->children.end()){
                background->children.erase(itr);
            }
        }
        cout<<"IDENTIFICATION: "<<childID<<endl;
        if (childID.find("WaterJet") != std::string::npos){
            // cout<<"THIS: "<<childID<<endl;
            for (DisplayObject* obj: foreground->children){
                string objID = obj->id;
                // cout<<"THAT: "<<obj->id<<" "<<obj->getSubtype()<<" "<<(objID.back() == childID.back()) <<endl;
                if ((obj->getSubtype()==12) && (objID.back() == childID.back())){
                    cout<<"RUNNING THROUGH THIS: "<<childID<<" "<<objID<<endl;
                    Valve* valve = (Valve*) obj;
                    WaterJet* waterjet = (WaterJet*) child;
                    valve->add_jet(waterjet);
                    waterjet->parent = valve;
                    cout<<"VALVE SIZE NOW: "<<valve->jets.size()<<endl;
                }
            }
            //remove door from background container
            vector<DisplayObject*>::iterator itr = find(foreground->children.begin(), foreground->children.end(), child);
            if (itr != background->children.end()){
                foreground->children.erase(itr);
            }
        }
    }
    pairedItems.clear();

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