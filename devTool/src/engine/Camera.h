#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include "DisplayObjectContainer.h"

using namespace std;

/**
 * Author: Bradley Knaysi
 * File: Camera.h
 * Created: March 20th, 2020
 * 
 * Source Code copyrighted by Lazy Foo' Productions (2004-2020)
 * I made expanded on their website's tutorial code
 */

class Camera : public DisplayObjectContainer {

    public:
        Camera();
        ~Camera();

        //Creates window
        bool init();

        //Handles window events
        void handleEvent( SDL_Event& e );

        //Focuses on window
        void focus();

        //Shows windows contents
        void render();

        //Decallocates internals
        void free();

        //Adds grid
        void addGrid();

        //Window dimensions
        int getWidth();
        int getHeight();
        int getGridCellSize();

        /**
         * CRITICAL TO APPLICATION
         * Internal method that returns a Camera's renderer.
         */
        SDL_Renderer* getRenderer();
        
        //Window focii
        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();
        bool isShown();

        //Game maintaining
        //Very important for maintaining the run-time polymorphism that recursively distributes data to all nodes
	    virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, SDL_Renderer* renderer );
	    virtual void draw( AffineTransform &at, SDL_Renderer* renderer );

    private:

        //Window data
        SDL_Window* window;
        SDL_Renderer* renderer;
        int windowID;

        //Window dimensions
        int width;
        int height;

        //Window grid
        bool grid;
        void drawGrid();

        //Window focus
        bool mouseFocus;
        bool keyboardFocus;
        bool fullScreen;
        bool minimized;
        bool shown;


        const int GRID_CELL_SIZE = 20;
        const int SCREEN_WIDTH = 640;
        const int SCREEN_HEIGHT = 480;

};

#endif