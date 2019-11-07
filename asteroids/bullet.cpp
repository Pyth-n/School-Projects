// Put your bullet methods here
/*********************************************
* Source file:
*    Bullet
* Author:
*    David Perez
* Summary:
*    Draws, and fires bullet according to angle
**********************************************/

#include "bullet.h"
#include "uiDraw.h"
#include <cmath>
#include <cassert>

using namespace std;
/******************************************
* BULLET : Constructors, sets bullet to alive
*****************************************/
Bullet::Bullet()
{
   // 0 frames at the beginning
   frameCount = 0;
}

/******************************************
* ADVANCE : Moves bullet towards direction of fire
*****************************************/
void Bullet::advance(Point tl, Point br)
{
   FlyingObject::advance(tl, br);
}

/******************************************
* DRAW : Draws the bullet
*****************************************/
void Bullet::draw() const
{
   drawDot(point);
}

/******************************************
* FIRE : Fires the bullet according to angle given
*****************************************/
void Bullet::fire(Point point, float angle, Velocity shipVelocity)
{
   assert(angle < 361 && angle > -361);
   // Sets point of bullet
   setPoint(point);

   // Uses same velocity as ship
   setVelocity(shipVelocity);

   // Sets direction and velocity of bullet to where the ship is
   float dx = velocity.getDx() + (BULLET_SPEED * (cos(M_PI / 180.0 * (angle + 90))));
   float dy = velocity.getDy() + (BULLET_SPEED * (sin(M_PI / 180.0 * (angle + 90))));
   velocity.setDx(dx);
   velocity.setDy(dy);
}
