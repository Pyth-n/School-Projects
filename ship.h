/***********************************************************************
* Header File:
*    Ship : Derivative of FlyingObject
* Author:
*    David Perez
* Summary:
*    Class has characteristics of ship, and functions that makes it move
************************************************************************/

#ifndef ship_h
#define ship_h

#include "flyingObject.h"
#include "bullet.h"
#include "uiDraw.h"

#define SHIP_SIZE 10
#define M_PI 3.14159265358979323846

#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

// Put your Ship class here
class Ship : public FlyingObject
{
private:
   int rotation;
   int radius;
   bool canThrust;
public:
   // Constructors
   Ship();
   virtual void draw() const;
   virtual void advance(Point tl, Point br);
   
   // Getters
   int getRotation()    const { return rotation; };
   int getRadius()      const { return radius; }
   bool canItThrust()   const { return canThrust; }

   // Controls ship
   void thrust();
   void moveRight();
   void moveLeft();
};

#endif /* ship_h */
