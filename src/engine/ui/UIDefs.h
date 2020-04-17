#ifndef UIDEFS_H
#define UIDEFS_H

#include "../Game.h"
#include "../DisplayObjectContainer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

// Please note for all UI elements, this is fine: camera->addChild(UI_element)
// Do NOT addChild with UI_element as the parent in MyGame.cpp! Something like UI_element->addChild(<x>) is going to break functionality of SelectionMenu.

class Text : public DisplayObjectContainer {
public:
    Text();
    Text(std::string content);

    void reloadFont();
    void setColor(int r, int g, int b);
    void setColor(SDL_Color color);

    ~Text();

    TTF_Font* font;
    SDL_Color fontColor = {255, 255, 255};
    std::string content = "";
    int fontSize = 12;
};

class TextBox : public DisplayObjectContainer{
public:
    // Note: A TextBox consists of both a box object (for background to text) and a Text class which contains the actual text content.
    TextBox(int posX = 0, int posY = 0, int width = 400, int height = 250);
    TextBox(std::string content, int posX = 0, int posY = 0, int width = 400, int height = 250);

    ~TextBox();

    void setText(std::string newText);
    void setFont(std::string path);
    void setFontColor(int r, int g, int b);
    void setFontColor(SDL_Color color);
    void setFontSize(int sz);
    
    virtual void draw(AffineTransform &at);

    Text* text;
};

// Effectively a TextBox with slightly altered functionality.
class SelectionMenu : public DisplayObjectContainer{
public:
    SelectionMenu(int posX = 0, int posY = 0, int width = 400, int height = 0);
    
    void addToMenu(std::string entry);
    void removeFromMenu(std::string entry);
    std::string getCurrentlySelected();
    // The currently-selected option should have a different color from every other option (to represent "active"). Handle that using these two functions.
    void incrementPosition();
    void decrementPosition();

    ~SelectionMenu();

    SDL_Color highlightedColor = {255, 215, 0};     // The selected text should have a different color.
    bool active;        // The selection menu should not choose an option unless the menu is active.
    int selectedIndex = -1;       // Position in the selection menu.
    std::vector<std::string> entries;   // The actual Text* objects are added to the 'children' attribute inherited from DOC.

    virtual void draw(AffineTransform &at);
};

class Checklist : public DisplayObjectContainer{
public:
    Checklist(int posX = 1025, int posY = 525, int width = 400, int height = 200);
    
    void addEntry(std::string entry);
    void removeEntry(std::string entry);
    void completeEntry(std::string entry);
    void completeEntry(int index);

    ~Checklist();

    SDL_Color completedColor = {0, 215, 0};     // The completed text should have a different color.
    bool active;        // The selection menu should not start checking tasks off unless it's active
    std::vector<std::string> entries;   // The actual Text* objects are added to the 'children' attribute inherited from DOC.

    virtual void draw(AffineTransform &at);
};

#endif
