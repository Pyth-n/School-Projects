/***********************************************************************
* Source File:
*    Ship : Implements code for the ship. Mainly draw and movements
* Author:
*    David Perez
* Summary:
*    Constructor, draws, advances its velocity, and moves
************************************************************************/

#include "ship.h"
#include <iostream>

/***************************************
* SHIP :: Constructor
***************************************/
Ship::Ship()
{
   // Ship defaults to point 0,0
   rotation = 0;
   radius = SHIP_SIZE;
   canThrust = true;
}

/***************************************
* SHIP :: draw
* Draws ship
***************************************/
void Ship::draw() const
{
   drawShip(point, rotation, canThrust);
}

/***************************************
* SHIP :: advance
* Advances unit at a time
***************************************/
void Ship::advance(Point tl, Point br)
{
   FlyingObject::advance(tl, br);

   // Once ship turns a 360, it will reset rotation to 0
   if ((getRotation() == 360) || (getRotation() == -360))
      rotation = 0;
   
   // Defaults to no flames
   canThrust = false;
}

/***************************************
* SHIP :: thrust
* Accelerates ship in current pointing direction
***************************************/
void Ship::thrust()
{
   // Enables flames when thrusting
   canThrust = true;
   // This will add inertia to the rocket
   float dx = velocity.getDx() + (THRUST_AMOUNT * (cos(M_PI / 180.0 * (rotation + 90))));
   float dy = velocity.getDy() + (THRUST_AMOUNT * (sin(M_PI / 180.0 * (rotation + 90))));
   velocity.setDx(dx);
   velocity.setDy(dy);
}

/***************************************
* SHIP :: moveRight
* Rotates the ship right
***************************************/
void Ship::moveRight()
{
   rotation -= ROTATE_AMOUNT;
}

/***************************************
* SHIP :: moveLeft
* Rotates the ship left
***************************************/
void Ship::moveLeft()
{
   rotation += ROTATE_AMOUNT;
}



