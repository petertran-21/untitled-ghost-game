#ifndef PARTICLE_H
#define PARTICLE_H

#include "DisplayObject.h"

using namespace std;

/**
 * Author: Bradley Knaysi
 * File: Particle.h
 * Created: April 14th, 2020
 * 
 * Influenced by Lazy Foo' Productions tutorial on
 * particle engines.
 */
class Particle : public DisplayObject
{
    public:

        Particle( int x, int y );
        ~Particle();

        virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState );
	    virtual void draw( AffineTransform &at );

    private:

        //Current frame of animation
        int frame;
};

#endif