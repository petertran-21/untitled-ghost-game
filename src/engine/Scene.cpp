#include "Scene.h"
#include "DisplayObjectContainer.h"
#include "EnvObjImports.h"
#include "CollectiblesImports.h"
#include "NPCObjImports.h"
#include "NPCImports.h"
#include "Ghost.h"
#include "particle_system/ParticleEmitter.h"
#include "BossImports.h"
#include "Camera.h"

Scene::Scene() : DisplayObjectContainer()
{
    type = "Scene";
    ghost = NULL;
    isGhostSentToCamera = false;
    isActive = true;
}

Scene::~Scene()
{
    type = "Scene";
    ghost = NULL;
    isGhostSentToCamera = false;
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
                //check which dir from the id
                if ((sprite["id"]).get<std::string>().find("Left") != std::string::npos) { cout<<"MADE LEFT VALVE"<<endl; unit = new Valve(Collisioncontainer, W);}
                else if ((sprite["id"]).get<std::string>().find("Right") != std::string::npos) { cout<<"MADE RIGHT VALVE"<<endl; unit = new Valve(Collisioncontainer, E);}
                else if (( sprite["id"]).get<std::string>().find("Up") != std::string::npos) { cout<<"MADE UP VALVE"<<endl; unit = new Valve(Collisioncontainer, N);}
                else { cout<<"MADE DOWN VALVE"<<endl; unit = new Valve(Collisioncontainer, S);}
                
                break;
            case BUTTON_SUBTYPE:
                unit = new Button(Collisioncontainer);
                break;
            case DOOR_SUBTYPE:
                unit = new Door(Collisioncontainer, foreground);
                //Collisioncontainer->addChild(unit);
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
                break;
            case NPCCOLLECTOR_SUBTYPE:
                unit = new NPCCollector(Collisioncontainer, foreground);
                break;
            case PIRATE_SUBTYPE:
                unit = new Pirate();
                break;
            case SNAKE_SUBTYPE:
                unit = new Snake(Collisioncontainer, foreground);
                break;
            case DRAGON_SUBTYPE:
                unit = new Dragon(Collisioncontainer, foreground);
                break;

            /*--------------------------Universal--------------------------*/
            case GHOST_SUBTYPE:
                unit = new Ghost();
                partEmit = new ParticleEmitter();
                unit->addChild(partEmit);
                Collisioncontainer->addChild(unit);

                //Part of Camera tracking Ghost pipeline
                this->ghost = (Ghost*) unit;

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
            for (DisplayObject* obj: foreground->children){
                string objID = obj->id;
                // cout<<"THAT: "<<objID<<endl;
                if (obj->getSubtype()==104 && (objID.back() == childID.back())){
                    cout<<"RUNNING THROUGH THIS: "<<childID<<" "<<objID<<endl;
                    Button* button = (Button*) obj;
                    Door* door = (Door*) child;
                    button->add_door(door);
                    //door->parent = button;
                    cout<<"BUTTON SIZE NOW: "<<button->doors.size()<<endl;
                }
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
                    //waterjet->parent = valve;
                    cout<<"VALVE SIZE NOW: "<<valve->jets.size()<<endl;
                    break;
                }
            }
            // //remove door from original container
            // vector<DisplayObject*>::iterator itr = find(foreground->children.begin(), foreground->children.end(), child);
            // if (itr != foreground->children.end()){
            //     foreground->children.erase(itr);
            // }
        }
    }
    pairedItems.clear();
    // for (DisplayObject* obj: foreground->children){
    //         string objID = obj->id;
    //         cout<<"THAT: "<<obj->id<<" "<<obj->getSubtype()<<endl;
    // }

    // Setting up parents
    for (auto it : needsParent){
        it.first->parent = parents[it.second];
        //cout << it.first->id << endl;
        //cout << it.second << endl;
        parents[it.second]->addChild(it.first);
    }

}

void Scene::update(set<SDL_Scancode> pressedKeys, Controller::JoystickState currState)
{
    //Part of Camera tracking Ghost pipeline
    if (isGhostSentToCamera == false )
    {
        if (this->parent != NULL) 
        {
            if (this->parent->type == "Camera")
            {
                Camera* camera = (Camera*) this->parent;
                camera->setGhost(this->ghost);
                isGhostSentToCamera = true;
            }
        }
    }

    DisplayObjectContainer::update(pressedKeys, currState);
}

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}
