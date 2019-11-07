/***********************************************************************
* Header File:
*    Rocks : Base of rock sizes. Derivative of FlyingObject
* Author:
*    David Perez
* Summary:
*    Every characteristics of each asteroid: Rotation, radius, and an abstract
*    virtual function of breakApart
************************************************************************/

#ifndef rocks_h
#define rocks_h
#include <list>
#include "flyingObject.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10
#define M_PI 3.14159265358979323846

/******************************************
* ROCKS : ABSTRACT BASE CLASS
*****************************************/
class Rocks : public FlyingObject
{
protected:
   int rotation;
   int radius;
public:
   // Constructors
   Rocks();
   // Getters
   int getRadius()   const { return radius; }
   int getRotation() const { return rotation; }

   // Setters
   void setRadius(int radius)       { this->radius = radius; }
   void setRotation(int rotation)   { this->rotation = rotation; }

   // Random point generator, used for initial large rocks
   Point randLocation();
   
   // Abstract virtual function
   virtual void breakApart(std::list <Rocks*> &rocks) = 0;
};

/******************************************
* LARGEROCK : Rock subclass
* Has individual point, velocity, 
* speed of advancing, and drawing type
*****************************************/
class LargeRock : public Rocks
{
private:
   // Starting angle of the large rocks (their direction of movement)
   int angle;
public:
   // Constructors
   LargeRock();
   LargeRock(Point point);

   // Draw, advance, break apart functions
   virtual void draw() const;
   virtual void advance(Point tl, Point br);
   virtual void breakApart(std::list <Rocks*> &rocks);
};

/******************************************
* MEDIUMROCK : Rock subclass
* Has individual point, velocity,
* speed of advancing, and drawing type
*****************************************/
class MediumRock : public Rocks
{
public:
   // Constructors
   MediumRock();
   MediumRock(Point point, Velocity velocity);

   // Draw, advance, break apart functions
   virtual void draw() const;
   virtual void advance(Point tl, Point br);
   virtual void breakApart(std::list <Rocks*> &rocks);
};

/******************************************
* SMALLROCK : Rock subclass
* Has individual point, velocity,
* speed of advancing, and drawing type
*****************************************/
class SmallRock : public Rocks
{
public:
   // Constructors
   SmallRock();
   SmallRock(Point point, Velocity velocity);

   // Draw, advance, break apart functions
   virtual void draw() const;
   virtual void advance(Point tl, Point br);
   virtual void breakApart(std::list <Rocks*> &rocks);
};

#endif /* rocks_h */
