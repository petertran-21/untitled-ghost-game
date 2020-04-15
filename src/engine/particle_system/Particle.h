#ifndef PARTICLE_H
#define PARTICLE_H

#include "DisplayObject.h"
#include "DisplayObjectContainer.h"
#include "Controls.h"

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

        Particle();
        ~Particle();

        virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState );
	    virtual void draw( AffineTransform &at );

    private:

        //The range in which a Particle can be draw
        int x_range;
        int y_range;

        //Current frame
        int frame;

        //Life of a particle
        static const int LIFE_SPAN = 100;

        //Trail length
        static const int TRAIL_LENGTH = 200;
};

#endif