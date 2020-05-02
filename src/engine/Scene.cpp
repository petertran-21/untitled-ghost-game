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
#include <iomanip>

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

void Scene::loadScene(string sceneFilePath, DisplayObjectContainer* Collisioncontainer, vector<DisplayObject*> &inventory){
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
    this->addChild(foreground);

    // vector<DisplayObject*> updatedInv=inventory;
    vector<DisplayObject*> pairedItems;
    for (auto sprite : j["sprites"]){
        // Get sprite subtype
        DisplayObject* filler = new DisplayObject();
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
                    sprite["isStaticBaseFile"] == "treeTop.png" ||
                    sprite["isStaticBaseFile"] == "mountainCorner1.png" ||
                    sprite["isStaticBaseFile"] == "mountainCorner2.png" ||
                    sprite["isStaticBaseFile"] == "mountainCorner3.png" ||
                    sprite["isStaticBaseFile"] == "mountainSide.png" ||
                    sprite["isStaticBaseFile"] == "mountainSide1.png" ||
                    sprite["isStaticBaseFile"] == "cavePitRight.png" ||
                    sprite["isStaticBaseFile"] == "cavePitLeft.png"
                ){
                    unit->type = "Wall";
                    Collisioncontainer->addChild(unit);
                }
                else{
                    unit->type = "Land";
                    cout<<sprite["isStaticBaseFile"]<<" "<<unit->type<<endl;
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
                unit = new NPCPyromancer(Collisioncontainer, foreground, inventory);
                break;
            case NPCLUMBERJACK_SUBTYPE:
                unit = new NPCLumberjack(Collisioncontainer, foreground, inventory);
                break;
            case NPCARCHER_SUBTYPE:
                unit = new NPCArcher(Collisioncontainer, foreground, inventory);
                break;
            case NPCSKELETON_SUBTYPE:
                unit = new NPCSkeleton(Collisioncontainer, foreground, inventory);
                break;
            case FORESTDOOR_SUBTYPE:
                unit = new ForestDoor(Collisioncontainer, inventory);
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
                unit = new NPCOperator(Collisioncontainer, foreground, inventory);
                break;
            case NPCEXCAVATOR_SUBTYPE:
                unit = new NPCExcavator(Collisioncontainer, foreground, inventory);
                break;
            case NPCCOLLECTOR_SUBTYPE:
                unit = new NPCCollector(Collisioncontainer, foreground, inventory);
                break;
            case PIRATE_SUBTYPE:
                unit = new Pirate();
                break;

            /*--------------------------Swamp--------------------------*/
            case HERB_SUBTYPE:
                unit = new Herb(Collisioncontainer);
                break;
            case BOAT_SUBTYPE:
                unit = new Boat(Collisioncontainer);
                break;
            case SWAMPTREE_SUBTYPE:
                unit = new SwampTree(Collisioncontainer, foreground);
                break;
            case SWAMPBRIDGE_SUBTYPE:
                if ((sprite["id"]).get<std::string>().find("notbuilt") != std::string::npos) {
                    unit = new SwampBridge(Collisioncontainer, false);
                }
                else{
                    unit = new SwampBridge(Collisioncontainer, true);
                }
                break;
            case CRAFTSTATION_SUBTYPE:
                unit = new CraftStation(Collisioncontainer);
                break;
            case POISONGAS_SUBTYPE:
                unit = new PoisonGas(Collisioncontainer);
                break;
            case SNAKE_SUBTYPE:
                unit = new Snake(Collisioncontainer, foreground);
                break;
            case NPCCROC_SUBTYPE:
                unit = new NPCCroc(Collisioncontainer, foreground, inventory);
                break;
            case NPCDOCTOR_SUBTYPE:
                unit = new NPCDoctor(Collisioncontainer, foreground, inventory);
                break;
            case NPCFISHERMAN_SUBTYPE:
                unit = new NPCFisherman(Collisioncontainer, foreground, inventory);
                break;
            case NPCBUILDER_SUBTYPE:
                unit = new NPCBuilder(Collisioncontainer, foreground, inventory);
                break;

            /*--------------------------Mountain--------------------------*/
            case DRAGON_SUBTYPE:
                unit = new Dragon(Collisioncontainer, foreground);
                break;
            case NPCSTRONGMAN_SUBTYPE:
                unit = new NPCStrongman(Collisioncontainer, foreground, inventory);
                break;
            case NPCCRAFTSMAN_SUBTYPE:
                unit = new NPCCraftsman(Collisioncontainer, foreground, inventory);
                break;
            case BOULDER_SUBTYPE:
                unit = new Boulder(Collisioncontainer);
                break;
            case MINERAL_SUBTYPE:
                unit = new Mineral(Collisioncontainer);
                break;
            case CAVELAKE_SUBTYPE:
                unit = new CaveLake(Collisioncontainer);
                break;
            case WORKBENCH_SUBTYPE:
                unit = new Workbench(Collisioncontainer);
                break;
            case SIGN_SUBTYPE:
                unit = new Sign(Collisioncontainer);
                break;
            case FALLENTREE_SUBTYPE:
                unit = new FallenTree(Collisioncontainer);
                break;
            case BUCKET_SUBTYPE:
                unit = new Bucket(Collisioncontainer);
                break;
            case MOUNTAINTREE_SUBTYPE:
                unit = new MountainTree(Collisioncontainer);
                break;

            /*--------------------------Universal--------------------------*/
            case GHOST_SUBTYPE:
                unit = new Ghost();
                partEmit = new ParticleEmitter();
                unit->addChild(partEmit);
                Collisioncontainer->addChild(unit);

                //Part of Camera tracking Ghost pipeline
                this->ghost = (Ghost*) unit;

                //Allows Ghost particles to change by biome
                partEmit->setBiome(sceneFilePath);

                break;
            case HORNFRAGMENT_SUBTYPE:
                unit = new HornFragment(Collisioncontainer);
                break;
            case MONUMENT_SUBTYPE:
                unit = new Monument(Collisioncontainer, inventory);
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

            if (unit->getSubtype() == SCENE_TRIGGER_SUBTYPE && sprite.find("ghostX") != sprite.end()){
                dynamic_cast<SceneTrigger*>(unit)->ghost_pos = {sprite["ghostX"], sprite["ghostY"]};
                cout << "Scene Trigger X Position " << sprite["ghostX"] << endl;
            }

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
    DisplayObjectContainer* foreground = static_cast<DisplayObjectContainer*>(this->getChild(1));
    for (int i = 0; i < foreground->numChildren(); i++) {
        DisplayObject* sprite = foreground->getChild(i);
        int subtype = sprite->getSubtype();
        if (subtype != SPRITE_SUBTYPE && subtype != SCENE_TRIGGER_SUBTYPE && subtype != DISPLAYOBJECTCONTAINER_SUBTYPE && subtype != GHOST_SUBTYPE && sprite->id != "EnvObj") {
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
            string parent = "foreground";
            /*
            if (sprite->parent != this){
                parent = sprite->parent->id;
                //cout << parent << endl;
            } else if (sprite->subtype != 2) {
                parent = "foreground";
            } */
            
            jsonSprite["parent"] = parent;
            j["sprites"].push_back(jsonSprite);
        }
    }
    
    // Save the scene
    std::ofstream o(this->FilePath);
    o << std::setw(4) << j << std::endl;
    }

void Scene::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}
