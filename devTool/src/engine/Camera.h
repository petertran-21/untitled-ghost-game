#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include "DisplayObjectContainer.h"
#include "AnimatedSprite.h"
#include "Sprite.h"

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
        Camera(int width, int height);
        ~Camera();

        //Creates window
        bool init();

        //Handles window events
        void handleEvent( SDL_Event& e );

        //Focuses on window
        void focus();

        //Adds grid
        void addGrid();

        //Global screen grid size
        static int getGridCellSize()
        {
            return GRID_CELL_SIZE;
        }

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
	    virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer );
	    virtual void draw( AffineTransform &at, SDL_Renderer* renderer, Mouse* mouse );

    private:

        //Window data
        SDL_Window* window;
        SDL_Renderer* renderer;
        int windowID;

        //Window grid
        static const int GRID_CELL_SIZE = 20;
        bool grid;
        void drawGrid();

        //Window focus
        bool mouseFocus;
        bool keyboardFocus;
        bool fullScreen;
        bool minimized;
        bool shown;      

};

#endif