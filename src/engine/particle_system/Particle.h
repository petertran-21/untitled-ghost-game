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

        /**
         * Particle Constructor
         * @param x offset from parent
         * @param y offset from parent
         * @param x_range of the spread
         * @param y_range of the spread
         */
        Particle( int x, int y, int x_range, int y_range );

        ~Particle();

        virtual void update( set<SDL_Scancode> pressedKeys, Controller::JoystickState currState );
	    virtual void draw( AffineTransform &at );

    private:

        //The range in which a Particle can be draw
        int x_range;
        int y_range;

        //Current frame
        int frame;
};

#endif