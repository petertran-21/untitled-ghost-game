#include "UIDefs.h"
#include <iostream>
#include <algorithm>

Inventory::Inventory(int posX, int posY, int width, int height) : DisplayObjectContainer(){
    DisplayObject::loadTexture("./resources/UI_BG.png");
    this->position.x = posX;
    this->position.y = posY;
    this->width = width;
    this->height = height;
    // DisplayObject* a = new DisplayObject();
    // this->entries.push_back(a);

}

Inventory::~Inventory(){
    DisplayObjectContainer::removeThis();
}

/* TO-DO: Can I skip the adding/removing as a whole and just update InventoryUI (in myGame) to = inventory?
*I don't think I even need addEntry, as the adding can occur via MainNPC's collision_resolution 
*/

/*
void Inventory::addEntry(DisplayObject obj){ //**to pass in a DO** or a std::string id and std::string imgPath...?
    this->entries.push_back(obj);
    DisplayObjectContainer* newItem = new DisplayObjectContainer(id,path);
    this->addChild(newItem);

    // Offset menu options.                                         // remember indexed at 0
    this->children.back()->position.x += (100 * (this->entries.size() - 1));
}
*/

/*Come to think of it, do I even need this method below in here? Shouldn't this logic be in the files handling
* interactions because they can just manipulate the inventory that myGame will just read from?
*/

/*
void Inventory::removeEntry(std::string id){ //if I take in DOs, can I search via id and delete appropriately? Or do I need to pass in DOs
    std::vector<DisplayObject> entries = this->entries; 
    entries.erase(std::remove_if(entries.begin(), entries.end(), [&](const DisplayObject & o){return o.id==id;}), entries.end());

    //DisplayObjectContainer* removeThis = new DisplayObjectContainer(id,);
    this->removeImmediateChild(id);        // Remove from the 'children' vector, which SelectionMenu inherits from DOC.
    // delete removeThis;
}
*/


void Inventory::draw(AffineTransform &at){
    DisplayObjectContainer::draw(at);
}