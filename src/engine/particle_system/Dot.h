#ifndef DOT_H
#define DOT_H

#include "DisplayObjectContainer.h"
#include "Particle.h"

using namespace std;

/**
 * Author: Bradley Knaysi
 * File: Dot.h
 * Created: April 14th, 2020
 * 
 * Influenced by Lazy Foo' Productions tutorial on
 * particle engines.
 */
class Dot : public DisplayObjectContainer
{
    public:

        Dot(int x, int y);
        ~Dot();

        virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState );
	    virtual void draw( AffineTransform &at );

    private:

        //Total number of particles
        static const int TOTAL_PARTICLES = 20;

        //The velocity of the dot
        int velocityX;
        int velocityY;

        //Maxiumum axis velocity of the dot
        static const int DOT_VELOCITY = 10;
};

#endif