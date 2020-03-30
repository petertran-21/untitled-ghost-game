#include "Scene.h"

Scene::Scene() : DisplayObjectContainer()
{
    this->type = "Scene";
}

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
            cout << unit->id << endl;
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

void Scene::saveScene(string sceneFilePath){
    json j;
    j["sprites"] = {json::array()};
    vector<DisplayObject*>* objects = Scene::getAllObjects(this);

    for (auto sprite : *objects){
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
            //cout << parent << endl;
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
            int lastslash = sprite->imgPath.find_last_of("/");
            jsonSprite["isStaticBaseFile"] = sprite->imgPath.substr(lastslash+1);
            jsonSprite["basePathFolder"] = sprite->imgPath.substr(0, lastslash+1);
        }
        cout << sprite->id << endl;
        j["sprites"].push_back(jsonSprite);
    }
    
    std::ofstream o(sceneFilePath + ".json");
    o << std::setw(4) << j << std::endl;
}

vector<DisplayObject*>* Scene::getAllObjects(DisplayObject* sprite){
    vector<DisplayObject*>* objects = new vector<DisplayObject*>();
    if (sprite->type != "Scene"){
        objects->push_back(sprite);
    }
    
    if (sprite->type == "DisplayObject"){
        return objects;
    } else {
        vector<DisplayObject*> spriteChildren = static_cast<DisplayObjectContainer*>(sprite)->children;
        for (auto child : spriteChildren){
            vector<DisplayObject*>* childsChildren = Scene::getAllObjects(child);
            objects->insert(objects->end(), childsChildren->begin(), childsChildren->end());
        }
    }
    return objects;
}

void Scene::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer )
{
    for( DisplayObject* character : children )
    {
        //Check if the current character meets the requirements of selection
        if( mouse->leftClick )
        {
            bool dragReq1 = character->position.x + this->position.x < mouse->selectBoxX;
            bool dragReq2 = mouse->selectBoxX < character->position.x + character->width + this->position.x;
            bool dragReq3 = character->position.y + this->position.y < mouse->selectBoxY;
            bool dragReq4 = mouse->selectBoxY < character->position.y + character->height + this->position.y;
            bool dragReq5 = mouse->selectBoxX2 == mouse->selectBoxX;
            bool dragReq6 = mouse->selectBoxY2 == mouse->selectBoxY;
            if( dragReq1 && dragReq2 && dragReq3 && dragReq4 && dragReq5 && dragReq6 )
            {
                character->selected = true;
				character->isBeingDragged = true;
				this->noSpritesSelected = false;
            }
            else if( !(dragReq5) && !(dragReq6) )
            {
                int topRX = -1;
                int topRY = -1;
                int botLX = -1;
                int botLY = -1;
                if(mouse->selectBoxX < mouse->selectBoxX2 && mouse->selectBoxY < mouse->selectBoxY2)
                {
                    // start is top left, current is bottom right
                    topRX = mouse->selectBoxX2;
                    topRY = mouse->selectBoxY;
                    botLX = mouse->selectBoxX;
                    botLY = mouse->selectBoxY2;
                } 
                else if(mouse->selectBoxX > mouse->selectBoxX2 && mouse->selectBoxY < mouse->selectBoxY2) 
                {
                    // start is top right, current is bottom left
                    topRX = mouse->selectBoxX;
                    topRY = mouse->selectBoxY;
                    botLX = mouse->selectBoxX2;
                    botLY = mouse->selectBoxY2;
                } 
                else if(mouse->selectBoxX < mouse->selectBoxX2 && mouse->selectBoxY > mouse->selectBoxY2) 
                {
                    // start is bottom left, , current is top right
                    topRX = mouse->selectBoxX2;
                    topRY = mouse->selectBoxY2;
                    botLX = mouse->selectBoxX;
                    botLY = mouse->selectBoxY;
                } 
                else if(mouse->selectBoxX > mouse->selectBoxX2 && mouse->selectBoxY > mouse->selectBoxY2) 
                {
                    // start is bottom right, , current is top left
                    topRX = mouse->selectBoxX;
                    topRY = mouse->selectBoxY2;
                    botLX = mouse->selectBoxX2;
                    botLY = mouse->selectBoxY;
                }

                bool selectReq1 = character->position.x + this->position.x < topRX;
                bool selectReq2 = botLX < character->position.x + character->width  + this->position.x;
                bool selectReq3 = character->position.y + character->height + this->position.y > topRY;
                bool selectReq4 = botLY > character->position.y + this->position.y;
                if( selectReq1 && selectReq2 && selectReq3 && selectReq4 ) 
                {
                    character->selected = true;
                    this->noSpritesSelected = false;
                }
            }
            else
            {
                character->selected = false;
            }

            if( character->isBeingDragged )
            {
				mouse->isDraggingObject = true;
				character->selected = true;
				character->position.x = (mouse->curCoords.x - this->position.x) - character->width/2;
				character->position.y = (mouse->curCoords.y - this->position.y) - character->height/2;
			}
        }   
        else 
        {
            mouse->isDraggingObject = false;
            character->isBeingDragged = false;
            character->position.x = character->position.x - (character->position.x % Camera::getGridCellSize());
            character->position.y = character->position.y - (character->position.y % Camera::getGridCellSize());
        }

        //Did the above requirements satisfy selectionf
        if (character->selected) 
        {
			if (pressedKeys.find(SDL_SCANCODE_Q) != pressedKeys.end()) 
            {
				character->width = ceil(1.1*character->width/Camera::getGridCellSize()) * Camera::getGridCellSize();
				character->height =  ceil(1.1*character->height/Camera::getGridCellSize()) * Camera::getGridCellSize();

			}
			if (pressedKeys.find(SDL_SCANCODE_W) != pressedKeys.end()) 
            {
				if (floor((character->width/1.1)/Camera::getGridCellSize()) == 0 || floor((character->height/1.1)/Camera::getGridCellSize()) == 0) 
                {
					character->width = 1 * Camera::getGridCellSize();
					character->height = 1 * Camera::getGridCellSize();
				} 
                else 
                {
					character->width = floor((character->width/1.1)/Camera::getGridCellSize()) * Camera::getGridCellSize();
					character->height = floor((character->height/1.1)/Camera::getGridCellSize()) * Camera::getGridCellSize();
				}
			}

			if (pressedKeys.find(SDL_SCANCODE_D) != pressedKeys.end()) 
            {
				// handle copy paste
				if (!this->duplicatedLastFrame)
                {
					this->duplicatedLastFrame = true;
					if (character->type == "Sprite")
                    {
						Sprite* copy = dynamic_cast<Sprite*>(character)->copy();
						this->addChild(copy);
						copy->position.x += 5 * Camera::getGridCellSize();
						copy->selected = false;
					}
					if (character->type == "AnimatedSprite")
                    {
						AnimatedSprite* copy = dynamic_cast<AnimatedSprite*>(character)->copy();
						this->addChild(copy);
						copy->position.x += 5 * Camera::getGridCellSize();
						copy->selected = false;
					}
				}
			} 
            else 
            {
				this->duplicatedLastFrame = false;
			}

			if (pressedKeys.find(SDL_SCANCODE_Z)!= pressedKeys.end())
            {
				character->alpha >= 255 ? character->alpha = 255 : character->alpha += 5;
			}

			if (pressedKeys.find(SDL_SCANCODE_X)!= pressedKeys.end())
            {
				character->alpha <= 0 ? character->alpha = 0 : character->alpha -= 5;
			}

			if (pressedKeys.find(SDL_SCANCODE_O)!= pressedKeys.end())
            {
				character->rotation += 0.05;
			}

			if (pressedKeys.find(SDL_SCANCODE_P)!= pressedKeys.end())
            {
				character->rotation -= 0.05;

			}

			if (pressedKeys.find(SDL_SCANCODE_I)!= pressedKeys.end())
            {
				cout << "Current id: " << character->id << endl;
				cout << "Change id (y/n)" << endl;
				string answer = "";
				cin >> answer;
				if (answer == "y")
                {
					cout << "New id: ";
					cin >> character->id;
				}
			}
		}
        else 
        {
		 		this->noSpritesSelected = true;
		}
    }

    if( noSpritesSelected ) 
    {
        if ( pressedKeys.find(SDL_SCANCODE_RIGHT) != pressedKeys.end() ) 
        {
            this->position.x -= Camera::getGridCellSize();
            //Game::dispGrid->position.x += 1;
        }
        if (pressedKeys.find(SDL_SCANCODE_LEFT) != pressedKeys.end()) {
            this->position.x += Camera::getGridCellSize();
        }
        if (pressedKeys.find(SDL_SCANCODE_DOWN) != pressedKeys.end()) {
            this->position.y -= Camera::getGridCellSize();
        }
        if (pressedKeys.find(SDL_SCANCODE_UP) != pressedKeys.end()) {
            this->position.y += Camera::getGridCellSize();
        }
    }

    //Load Scene
    if( pressedKeys.find(SDL_SCANCODE_L) != pressedKeys.end() )
    {
        cout << "Load Scene: ";
        string scenePath = "./resources/scenes/";
        string sceneName;
        cin >> sceneName;
        cout << scenePath + sceneName << endl;
        try{
            this->loadScene(scenePath + sceneName + ".json");
        } catch(exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    if (pressedKeys.find(SDL_SCANCODE_S) != pressedKeys.end())
    {
		cout << "Save Scene: ";
		string scenePath = "./resources/scenes/";
		string sceneName;
		cin >> sceneName;
		cout << scenePath + sceneName << endl;
		this->saveScene(scenePath + sceneName);
	}

    DisplayObjectContainer::update( pressedKeys, currState, mouse, renderer );
}

void Scene::draw( AffineTransform &at, SDL_Renderer* renderer, Mouse* mouse )
{
    DisplayObjectContainer::draw( at, renderer, mouse );
}