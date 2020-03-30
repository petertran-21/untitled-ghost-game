#include "Camera.h"

/**
 * Author: Bradley Knaysi
 * File: Camera.h
 * Created: March 20th, 2020
 * 
 * Source Code copyrighted by Lazy Foo' Productions (2004-2020)
 * I made expanded on their website's tutorial code
 */

Camera::Camera() : DisplayObjectContainer()
{
    window = NULL;
    renderer = NULL;
    windowID = -1;
    
    width = 640;
    height = 480;
    grid = false;

    mouseFocus = false;
    keyboardFocus = false;
    shown = false;
}

Camera::Camera( int width, int height ) : DisplayObjectContainer()
{
    window = NULL;
    renderer = NULL;
    windowID = -1;
    
    this->width = width;
    this->height = height;
    grid = false;

    mouseFocus = false;
    keyboardFocus = false;
    shown = false;
}

Camera::~Camera()
{
    if( window != NULL )
    {
        SDL_DestroyWindow( window );
    }
    if( renderer != NULL )
    {
        SDL_DestroyRenderer( renderer );
    }

    window = NULL;
    renderer = NULL;
    mouseFocus = false;
    keyboardFocus = false;
    width = 0;
    height = 0;
}

bool Camera::init()
{
    //Create window
    window = SDL_CreateWindow( "Untilted Ghost Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if ( window != NULL ) 
    {
        mouseFocus = true;
        keyboardFocus = true;

        //Create renderer for window
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if ( renderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            SDL_DestroyWindow( window );
            window = NULL;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( renderer, 120, 120, 120, 1 );

            //Grab window identifier
            windowID = SDL_GetWindowID( window );

            //Flag as opened
            shown = true;
        }
    }
    else
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    }

    bool status = (window != NULL && renderer != NULL);
    return status;
    
}

void Camera::handleEvent( SDL_Event& e )
{
    //If an event was detected for this window
    if( e.type == SDL_WINDOWEVENT && e.window.windowID == windowID )
    {
        //Caption update flag
        bool debuggerFlag = false;

        switch( e.window.event )
        {
            //Window appeared
            case SDL_WINDOWEVENT_SHOWN:
			    shown = true;
			    break;

            //Window disappeared
			case SDL_WINDOWEVENT_HIDDEN:
			    shown = false;
			    break;

            //Get new dimensions and repaint
			case SDL_WINDOWEVENT_SIZE_CHANGED:
                width = e.window.data1;
                height = e.window.data2;
                SDL_RenderPresent( renderer );
                break;

            //Repaint on expose
			case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent( renderer );
                break;

            //Mouse enter
			case SDL_WINDOWEVENT_ENTER:
                mouseFocus = true;
                debuggerFlag = true;
                break;

            //Mouse exit
			case SDL_WINDOWEVENT_LEAVE:
                mouseFocus = false;
                debuggerFlag = true;
                break;

            //Keyboard focus gained
			case SDL_WINDOWEVENT_FOCUS_GAINED:
                keyboardFocus = true;
                debuggerFlag = true;
                break;

            //Keyboard focus lost
			case SDL_WINDOWEVENT_FOCUS_LOST:
                keyboardFocus = false;
                debuggerFlag = true;
                break;

            //Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
                minimized = true;
                break;

            //Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
                minimized = false;
                break;

            //Window restored
			case SDL_WINDOWEVENT_RESTORED:
                minimized = false;
                break;

            //Hide on close
			case SDL_WINDOWEVENT_CLOSE:
                SDL_HideWindow( window ); // might be causing "Segmentation fault: 11" error b/c calls destructor but a window is still open
                break;
        }

        //Update window caption with new data
        if( debuggerFlag )
        {
            stringstream caption;
			caption << "Camera - ID: " << windowID << " MouseFocus:" << ( ( mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( keyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle( window, caption.str().c_str() );

        }
    }
}

void Camera::focus()
{
    //Restore window if needed
    if( !shown )
    {
        SDL_ShowWindow( window );
    }

    //Move window forward
    SDL_RaiseWindow( window );
}

void Camera::drawGrid()
{
    int numVertical = 1 + width;
    int numHorizontal = 1 + height;

    //Change the draw color
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 1);

    for (int c = 0; c < numVertical; c += GRID_CELL_SIZE) 
    {
    SDL_RenderDrawLine(renderer, c, 0, c, height);
    }
    for (int r = 0; r < numHorizontal; r += GRID_CELL_SIZE) 
    {
    SDL_RenderDrawLine(renderer, 0, r, width, r);
    }
}

void Camera::update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState, Mouse* mouse, SDL_Renderer* renderer )
{
	DisplayObjectContainer::update( pressedKeys, currState, mouse, renderer );
}

void Camera::draw( AffineTransform &at, SDL_Renderer* renderer, Mouse* mouse )
{
    //Clear screen
    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 1);
    SDL_RenderClear(renderer);

    //Draw grid
    if( grid )
    {
        drawGrid();
    }

    //Draw children
	DisplayObjectContainer::draw( at, renderer, mouse );

    //Draw mouse select box
    mouse->drawSelectBox( renderer );

    //Update screen
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Camera::getRenderer()
{
    return renderer;
}

void Camera::addGrid()
{
    grid = true;
}

bool Camera::hasMouseFocus()
{
    return mouseFocus;
}

bool Camera::hasKeyboardFocus()
{
    return keyboardFocus;
}

bool Camera::isMinimized()
{
    return minimized;
}

bool Camera::isShown()
{
    return shown;
}