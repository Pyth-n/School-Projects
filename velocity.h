/***********************************************************************
* Header File:
*    Velocity : Sets velocity for x and y axis
* Author:
*    David Perez
* Summary:
*    Sets velocity for both axis.
************************************************************************/

#ifndef VELOCITY_H
#define VELOCITY_H

// Put your velocity class here, or overwrite this file with your own
// velocity class from the previous project
class Velocity
{
private:
   float dX;
   float dY;
public:
   // Constructors
   Velocity();
   Velocity(float, float);

   // Getters
   float getDx() const { return dX; }
   float getDy() const { return dY; }

   // Setters
   void setDx(float x) { this->dX = x; }
   void setDy(float y) { this->dY = y; }

   // Add
   void addDx(float x) { this->dX += x; }
   void addDy(float y) { this->dY += y; }
};


#endif /* velocity_h */
