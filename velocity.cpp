/*********************************************
* Source file:
*    Velocity
* Author:
*    David Perez
* Summary:
*    Stores velocity for x and y axis
**********************************************/
#include "velocity.h"
#include <iostream>

/******************************************
* VELOCITY :: VELOCITY
* Constructors
******************************************/
Velocity::Velocity()
{
   dX = 0.0;
   dY = 0.0;
}

Velocity::Velocity(float dX, float dY)
{
   this->dX = dX;
   this->dY = dY;
}

