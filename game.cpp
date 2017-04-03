/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

#include "rocks.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

#define OFF_SCREEN_BORDER_AMOUNT 5

/***************************************
* GAME :: Constructors
***************************************/
Game :: Game(Point t1, Point br)
{
   // Default values starting the game
   this->topLeft = t1;
   this->bottomRight = br;

   // Displayed numbers
   this->numBullets = 0;
   this->numLives = 3;
   this->score = 0;
   this->hiScore = readScore();
   this->wrote = false;
   // Let's start NULL
   rocket = NULL;

   // Game starts with 5 rocks
   createLargeRocks();
}

Game :: ~Game()
{
   // Deletes memory at the end
   list <Rocks*>::iterator it = rock.begin();
   for (it; it != rock.end(); )
   {
      delete *it;
      it = rock.erase(it);
      it++;
   }

   vector <Bullet*>::iterator bIt = bullets.begin();
   for (bIt; bIt < bullets.end(); )
   {
      delete *it;
      bIt = bullets.erase(bIt);
      bIt++;
   }

   delete rocket;
   rocket = NULL;
}

/***************************************
* GAME :: HANDLE INPUT
* accept input from the user
***************************************/
void Game::handleInput(const Interface & ui)
{
   if (rocket != NULL && rocket->isAlive())
   {
      if (ui.isLeft())
      {
         rocket->moveLeft();
      }

      if (ui.isRight())
      {
         rocket->moveRight();
      }
      if (ui.isUp())
      {
         rocket->thrust();
      }
      if (ui.isSpace())
      {
         Bullet *bullet = new Bullet;
         (*bullet).fire(rocket->getPoint(), rocket->getRotation(), rocket->getVelocity());

         bullets.push_back(bullet); // Adds bullet pointer to vector
         numBullets++; // Increase number of bullets when fired
      }
   }
}

/***************************************
* GAME :: ADVANCE
* advance the game one unit of time
***************************************/
void Game::advance()
{
   advanceRocket();
   advanceRocks();
   advanceBullets();
   handleCollisions();
   cleanUpZombies();
}

/***************************************
* GAME :: ADVANCElr
* Advances asteroids
***************************************/
void Game::advanceRocks()
{
   // Advance rocks
   list <Rocks*>::iterator it = rock.begin();
   while (it != rock.end())
   {
      (*it)->advance(getTopLeft(), getBottomRight());
      it++;
   }
}

/***************************************
* GAME :: ADVANCEBULLETS
* Advances bullets towards direction
***************************************/
void Game::advanceBullets()
{
   for (vector <Bullet*>::iterator it = bullets.begin(); it < bullets.end();)
   {
      if ((*it)->isAlive())
      {
         (*it)->advance(getTopLeft(), getBottomRight());
         (*it)->upFrame();
         
         if ((*it)->getFrameCount() == 40)
         {
            (*it)->kill();
         }
      }
      it++;
   }
}

/***************************************
* GAME :: CREATEROCK
* Adds 5 rocks to the rock list
***************************************/
void Game::advanceRocket()
{
   if (rocket == NULL && numLives > 0)
   {
      rocket = createRocket();
   }
   else if (rocket != NULL && rocket->isAlive())
   {
      rocket->advance(getTopLeft(), getBottomRight());
   }
}

/***************************************
* GAME :: CREATEROCK
* Adds 5 rocks to the rock list
***************************************/
void Game::createLargeRocks()
{
   for (int i = 0; i < 5; i++)
   {
      LargeRock* newRock = new LargeRock;
      rock.push_back(newRock);
   }
}

/***************************************
* GAME :: CREATESHIP
* Creates rocket if none is allocated
***************************************/
Ship* Game::createRocket()
{
   Ship* newShip = new Ship;
   return newShip;
}


/**************************************************************************
* GAME :: CLEAN UP ZOMBIES
* Remove any dead objects (take bullets out of the list)
**************************************************************************/
void Game::cleanUpZombies()
{
   // Deletes killed bullets
   for (vector <Bullet*>::iterator it = bullets.begin(); it < bullets.end();)
   {
      if (!(*it)->isAlive() && *it != NULL)
      {
         delete *it;
         *it = NULL;
         it = bullets.erase(it);
      }
      else
         it++;
   }

   // Deletes killed rocks
   for (list <Rocks*>::iterator it = rock.begin(); it != rock.end();)
   {
      if (!(*it)->isAlive() && *it != NULL)
      {
         delete *it;
         *it = NULL;
         it = rock.erase(it);
      }
      else
         it++;
   }

   // Delete killed ship
   if (rocket != NULL && !rocket->isAlive())
   {
      delete rocket;
      rocket = NULL;
   }
}

/**************************************************************************
* GAME :: HANDLE COLLISIONS
* Check for a collision between a asteroid and a bullet/ship.
**************************************************************************/
void Game::handleCollisions()
{
   // Detects collision between rock and ship, if hits, decreases lives
   if (rocket != NULL && rocket->isAlive())
   {
      for (list <Rocks*>::iterator rocky = rock.begin(); rocky != rock.end(); )
      {
         if (getClosestDistance(**rocky, *rocket) <= (*rocky)->getRadius() + rocket->getRadius())
         {
            (*rocky)->kill();
            rocket->kill();
            cout << "\7";
            numLives--;
            score -= 2;
         }
         if (!(*rocky)->isAlive())
            (*rocky)->breakApart(rock);
         rocky++;
      }
   }

   // Detects collision between bullet and rock
   for (vector <Bullet*>::iterator bull = bullets.begin(); bull != bullets.end(); )
   {
      for (list <Rocks*>::iterator rocky = rock.begin(); rocky != rock.end(); )
      {
         if (getClosestDistance(**rocky, **bull) <= (*rocky)->getRadius() + 10)
         {
            (*rocky)->kill();
            (*bull)->kill();
            score++;
         }
         if (!(*rocky)->isAlive())
            (*rocky)->breakApart(rock);
         rocky++;
      }
      bull++;
   }
}

/**************************************************************************
* GAME :: IS ON SCREEN
* Determines if a given point is on the screen.
**************************************************************************/
bool Game::isOnScreen(const Point & point)
{
   return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
      && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
      && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
      && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/*********************************************
* GAME :: DRAW
* Draw everything on the screen
*********************************************/
void Game::draw(const Interface & ui)
{
   // Iterator for rocks
   list <Rocks*>::iterator it = rock.begin();
  
   while (it != rock.end())
   {
      if ((*it)->isAlive() && *it != NULL)
      {
         (*it)->draw();
      }
      it++;
   }
   
   // Iterator for bullets
   for (vector <Bullet*>::iterator it = bullets.begin(); it < bullets.end();)
   {
      if ((*it)->isAlive() && *it != NULL)
      {
         (*it)->draw();
      }
      it++;
   }

   // Draws if rocket is alive, otherwise it draws game over
   if (rocket != NULL && rocket->isAlive())
      rocket->draw();

   // No lives left!
   if (numLives == 0)
   {
      // Write score
      if (!wrote)
      {
         writeScore(score);
         hiScore = readScore();
         wrote = true;
      }
      
      // Game over
      Point gameOver(-40, 0);
      drawText(gameOver, "GAME OVER");

      // Score
      Point sText(-40, -18);
      drawText(sText, "Score:");
      Point scoreNum(3,-8);
      drawNumber(scoreNum, score);

      // Hiscore
      Point hText(-40, -36);
      drawText(hText, "HiScore:");
      Point hNum(12, -26);
      drawNumber(hNum, hiScore);
   }

   // Displays score, lives
   if (numLives > 0)
   {
      Point sText(130, 140);
      drawText(sText, "Score:");
      Point sNum(172, 150);
      drawNumber(sNum, score);

      Point lText(-200, 185);
      drawText(lText, "Lives:");
      Point lNum(-165, 195);
      drawNumber(lNum, numLives);
   }

   // Draw # of bullets fired
   Point bText(130, 180);
   drawText(bText, "Bullets:");
   Point bNum(172, 190);
   drawNumber(bNum, numBullets);

   // Draw # of rocks left
   Point rText(130, 160);
   drawText(rText, "Rocks:");
   Point rNum(172, 170);
   drawNumber(rNum, rock.size());
}

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/**********************************************************
* Function: readScore
* Reads previous score
**********************************************************/
int Game::readScore()
{
   ifstream fin("score.txt");

   if (fin.fail()) // if file doesn't exist, returns a 0
   {
      return 0;
   }

   // Load previous score
   int score = 0;
   fin >> score;

   // Close and return
   fin.close();
   return score;
}

/**********************************************************
* Function: writeScore
* Writes the HISCORE, if its not new, it keeps old value
**********************************************************/
void Game::writeScore(int score)
{
   ifstream fin("score.txt");
   if (fin.fail())
      return;
   int oldScore;
   fin >> oldScore;
   fin.close();

   ofstream fout("score.txt");
   
   if (fout.fail())
      return;  // Prevents writing error if opening this stream fails

   // Checks for higher score
   if (score > oldScore)
      fout << score;
   else
      fout << oldScore;

   fout.close();
   return;
}
