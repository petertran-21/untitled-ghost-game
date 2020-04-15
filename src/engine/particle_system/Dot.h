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

        Dot();
        ~Dot();

        virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState );
	    virtual void draw( AffineTransform &at );

    private:

        //Total number of particles
        static const int TOTAL_PARTICLES = 20;

        //Dot to parent ratio
        const double PARENT_TO_DOT_RATIO = 0.80;
};

#endif