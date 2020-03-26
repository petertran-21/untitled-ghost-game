#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include "AffineTransform.h"
#include <iostream>

/**
 * Affine Transforms
 * 
 * */
AffineTransform::AffineTransform()
{
	transform = identity();
}

AffineTransform::~AffineTransform()
{
	cleanMatrix(transform);
}

void AffineTransform::cleanMatrix(double **m)
{
	for (int i = 0; i < 3; i++)
		delete m[i];
	delete m;
}

/* Returns the identity matrix as an array */
double **AffineTransform::identity()
{
	double **id = new double *[3];
	for (int i = 0; i < 3; i++)
	{
		id[i] = new double[3];
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
				id[i][j] = 1.0;
			else
				id[i][j] = 0.0;
		}
	}
	return id;
}

/* Takes a point in the local coordinate system and transforms it to global space given this AffineTransform */
SDL_Point AffineTransform::transformPoint(int x, int y)
{
	SDL_Point temp;
	temp.x = (x * transform[0][0]) + (y * transform[0][1]) + (1 * transform[0][2]);
	temp.y = (x * transform[1][0]) + (y * transform[1][1]) + (1 * transform[1][2]);
	return temp;
}

/* Add another transform to this one, is basically just matrix multiply */
void AffineTransform::concatenate(AffineTransform &at)
{
	// calculate the multiplication
	double result[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				result[i][j] += this->transform[i][k] * at.transform[k][j];
			}
		}
	}
	// copy it into the transform matrix
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->transform[i][j] = result[i][j];
		}
	}
	return;
}

/* Move points in the x and y direction */
void AffineTransform::translate(int x, int y)
{
	AffineTransform at;
	// set transform[0][2] to x
	at.transform[0][2] = x;
	// set transform[1][2] to y
	at.transform[1][2] = y;
	concatenate(at);
}

/* rotate points by r radians */
void AffineTransform::rotate(double r)
{
	AffineTransform at;
	// set transform[0][0] to cos(r)
	at.transform[0][0] = cos(r);
	// set transform[0][1] to -sin(r)
	at.transform[0][1] = -sin(r);
	// set transform[1][0] to sin(r)
	at.transform[1][0] = sin(r);
	// set transform[1][1] to cos(r)
	at.transform[1][1] = cos(r);
	concatenate(at);
}

/* scale in the x and y direction accordingly */
void AffineTransform::scale(double x, double y)
{
	AffineTransform at;
	// set transform[0][0] to x
	at.transform[0][0] = x;
	// set transform[1][1] to y
	at.transform[1][1] = y;
	concatenate(at);
}

double AffineTransform::getScaleX()
{
	//TODO in future assignment
	return transform[0][0];
}

double AffineTransform::getScaleY()
{
	//TODO in future assignment
	return transform[1][1];
}