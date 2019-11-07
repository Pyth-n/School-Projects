#include "flyingObject.h"
#include <iostream>

/******************************************
* BULLET : Constructor
*****************************************/
FlyingObject::FlyingObject()
{
   alive = true;
}

/******************************************
* BULLET : 
*****************************************/
void FlyingObject::advance(Point tl, Point br)
{
   // Wraps x-axis
   if (point.getX() > br.getX())
      point.setX(point.getX() * -1);
   else if (point.getX() < tl.getX())
      point.setX(point.getX() * -1);

   // Wrap y-axis
   if (point.getY() > tl.getY())
      point.setY(point.getY() * -1);
   else if (point.getY() < br.getY())
      point.setY(point.getY() * -1);

   // Advances the objects to their velocity
   point.addX(velocity.getDx());
   point.addY(velocity.getDy());
}

void FlyingObject::kill()
{
   setAlive(false);
}