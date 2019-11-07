/***********************************************************************
* Source File:
*    Rocks : Base and subclasses; Large, medium, small asteroid
* Author:
*    David Perez
* Summary:
*    Contains individual polymorphed characteristics of each class
************************************************************************/

#include "rocks.h"
#include "uiDraw.h"

/******************************************
* ROCKS : CONSTRUCTOR w/ DEFAULTS
* Initialize the rocks to not be hit, 0 rotation
*****************************************/
Rocks::Rocks()
{
   // Default of 0 rotation for all rocks
   this->rotation = 0;
   this->radius = 0;
}

/******************************************
* ROCKS : randLocation
* Generates and returns a random starting point
*****************************************/
Point Rocks::randLocation()
{
   Point newPoint(random(-200, 200), random(-200, 200));
   
   return newPoint;
}

/******************************************
* LARGEROCK : Constructor
* Sets the default velocity, point, and start of rotation
*****************************************/
LargeRock::LargeRock()
{
   // Random position on screen when instintiated
   setPoint(randLocation());

   // Random starting angle
   angle = random(-360, 360);

   // Velocity set with random angle
   float dx = velocity.getDx() + (cos(M_PI / 180.0 * (angle + 90)));
   float dy = velocity.getDy() + (sin(M_PI / 180.0 * (angle + 90)));
   velocity.setDx(dx);
   velocity.setDy(dy);

   // Default radius
   radius = BIG_ROCK_SIZE;
}

/******************************************
* LARGEROCK : Constructor
* Sets a point when institiated with arguments
*****************************************/
LargeRock::LargeRock(Point point)
{
   this->point = point;
}

/******************************************
* LARGEROCK : DRAW
* Draws the asteroid with its point and rotation
*****************************************/
void LargeRock::draw() const
{
   drawLargeAsteroid(point, rotation);
}

/******************************************
* LARGEROCK : Advance
* This rotates and also sets the velocity of the asteroid
*****************************************/
void LargeRock::advance(Point tl, Point br)
{
   // Enables screen wrapping and moves to its velocity
   FlyingObject::advance(tl, br);

   // Asteroid rotates 2 degrees per frame
   rotation += BIG_ROCK_SPIN;
}

/******************************************
* LARGEROCK : breakApart
* Pushes new rocks back to the list when a large rock is hit
*****************************************/
void LargeRock::breakApart(std::list <Rocks*> &rocks)
{
   // Medium rock 1 and its new velocity
   Velocity medVel(velocity.getDx(), 1);
   MediumRock* lol = new MediumRock(point, medVel);
   rocks.push_back(lol);
   
   // Medium Rock 2 and its new velocity
   Velocity medVel2(velocity.getDx(), -1);
   MediumRock* lol2 = new MediumRock(point, medVel2);
   rocks.push_back(lol2);

   // Small rock and its new velocity
   Velocity smVel(velocity.getDx() + 2, 1);
   SmallRock* lol3 = new SmallRock(point, smVel);
   rocks.push_back(lol3);
}

/******************************************
* MEDIUMROCK : CONSTRUCTOR w/ DEFAULTS
* Currently empty, derives base constructors
*****************************************/
MediumRock::MediumRock()
{
   // Default radius
   radius = MEDIUM_ROCK_SIZE;
}

/******************************************
* MEDIUMROCK : Constructor
* Sets a point when institiated with arguments
*****************************************/
MediumRock::MediumRock(Point point, Velocity velocity)
{
   this->point = point;
   this->velocity = velocity;
}

/******************************************
* MEDIUMROCK : DRAW
* Draws the asteroid with its point and rotation
*****************************************/
void MediumRock::draw() const
{
   drawMediumAsteroid(point, rotation);
}

/******************************************
* SMALLROCK : Advance
* This rotates and also sets the velocity of the asteroid
*****************************************/
void MediumRock::advance(Point tl, Point br)
{
   // Enables screen wrapping and moves to its velocity
   FlyingObject::advance(tl, br);

   // Asteroid rotates 5 degrees per frame
   rotation += MEDIUM_ROCK_SPIN;
}

/******************************************
* LARGEROCK : breakApart
* Pushes back to the list new rocks
*****************************************/
void MediumRock::breakApart(std::list <Rocks*> &rocks)
{
   // Small asteroid and its new velocity
   Velocity smVel(velocity.getDx() + 3, velocity.getDy());
   SmallRock* rock1 = new SmallRock(point, smVel);
   rocks.push_front(rock1);

   // Small asteroid and its new velocity
   Velocity smVel2(velocity.getDx() - 3, velocity.getDy());
   SmallRock* rock2 = new SmallRock(point, smVel2);
   rocks.push_front(rock2);
}

/******************************************
* SMALLROCK : CONSTRUCTOR w/ DEFAULTS
* Currently empty, derives base constructors
*****************************************/
SmallRock::SmallRock()
{
   // Default radius
   radius = SMALL_ROCK_SIZE;
}

/******************************************
* SMALLROCK : Constructor
* Sets a point when institiated with arguments
*****************************************/
SmallRock::SmallRock(Point point, Velocity velocity)
{
   this->point = point;
   this->velocity = velocity;
}

/******************************************
* SMALLROCK : DRAW
* Draws the asteroid with its point and rotation
*****************************************/
void SmallRock::draw() const
{
   drawSmallAsteroid(point, rotation);
}

/******************************************
* SMALLROCK : Advance
* This rotates and also sets the velocity of the asteroid
*****************************************/
void SmallRock::advance(Point tl, Point br)
{
   // Enables screen wrapping and moves to its velocity
   FlyingObject::advance(tl, br);

   // Asteroid rotates 10 degrees per frame
   rotation += SMALL_ROCK_SPIN;
}

/******************************************
* SMALLROCK : breakApart
* Pushes back to the list new rocks
*****************************************/
void SmallRock::breakApart(std::list <Rocks*> &rocks)
{
   // Rocks delete in handleCollision()
}
