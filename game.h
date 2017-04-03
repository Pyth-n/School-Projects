/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>
#include "uiDraw.h"
#include "uiInteract.h"
#include "velocity.h"
#include "point.h"

// Asteroids and ship
#include "rocks.h"
#include "ship.h"
#include "bullet.h"

class Game
{
private:
   Point topLeft;
   Point bottomRight;

   bool isOnScreen(const Point & point); 
   bool wrote;
   int numBullets;
   int numLives;
   int score;
   int hiScore;
   // Create ship, rock list, bullet vector
   Ship* rocket;
   std::list <Rocks*> rock;
   std::vector <Bullet*> bullets;

   void createLargeRocks();
   Ship* createRocket();
   /*************************************************
   * Private methods to help with the game logic.
   *************************************************/
   void advanceRocks();
   void advanceBullets();
   void advanceRocket();
   void handleCollisions();
   void cleanUpZombies();

   int readScore();              // Reads from score.txt
   void writeScore(int score);   // Writes score to score.txt

public:
   Game(Point t1, Point br); 
   ~Game(); 
   void handleInput(const Interface & ui); 
   void advance(); 
   void draw(const Interface & ui);

   // Returns distance between objects
   float getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const;


   Point getTopLeft()         { return topLeft; }
   Point getBottomRight()     { return bottomRight; }
};

#endif /* GAME_H */
