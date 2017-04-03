/***********************************************************************
* Header File:
*    FlyingObject
* Author:
*    David Perez
* Summary: ABSTRACT
*    Base class for anything that is in the air; points and velocity
************************************************************************/

#ifndef flyingObject_h
#define flyingObject_h

// Put your FlyingObject class here
#include "point.h"
#include "velocity.h"

class FlyingObject
{
protected:
   Point point;
   Velocity velocity;
   bool alive;
public:
   FlyingObject();

   // Getters
   Point getPoint()              const { return point; }
   Velocity getVelocity()        const { return velocity; }
   bool isAlive()                const { return alive; }

   // Setters
   void setAlive(bool alive) { this->alive = alive; }
   void setPoint(Point point) { this->point = point; }
   void setVelocity(Velocity velocity) { this->velocity = velocity; }
   // Drawing, and advancing, and killing
   void kill();
   virtual void draw() const = 0;
   virtual void advance(Point tl, Point br);
};



#endif /* flyingObject_h */
