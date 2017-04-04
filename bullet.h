#ifndef bullet_h
#define bullet_h

#include "flyingObject.h"

#define BULLET_SPEED 5
#define BULLET_LIFE 40
#define M_PI 3.14159265358979323846


// Put your Bullet class here
class Bullet : public FlyingObject
{
private:
   // Will count the amount of frames for the death of bullet
   int frameCount;

public:
   // Constructors
   Bullet();

   // Getters
   int getFrameCount() const { return frameCount; }

   // Increases frame count by 1
   void upFrame() { frameCount += 1; }

   // Draws and runs
   virtual void advance(Point tl, Point br);
   virtual void draw() const;

   // Controls and kills bullet
   void fire(Point point, float angle, Velocity shipVelocity);
};

#endif /* bullet_h */
