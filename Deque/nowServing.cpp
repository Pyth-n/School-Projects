/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
*    Jeffry Simpson, David Perez 
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE

using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   string  chooser;                                   //Input for Menu choices
   string course, name,time;
   eChoice picked;                                    //enum translated Menu choice
    int    linecount =  0,                            //Simulator counter
           minsLeft =  0;                             //Minutes left for current student
   Deque<Student> serving;                            //Deque of Students waiting
   Student current, nxt;                              //Current and New student
   
   
   displayInstructions();                             //Print the instructions
   
   do
   {
      cout << "<" << linecount++ << "> ";             //Simulator line output
      
      cin.ignore();
      cin.clear();
      cin >> chooser;
      
      picked = string2enum(chooser);                  //change string to enum
      
      switch (picked)
      {
         case NONE:                                   //Simulator incrementor only
         {
            if( minsLeft <= 0)                        //Current student is done
               if(!serving.empty())                   //Check for more students
               {
                  current = serving.front();          //Get next student
                  serving.pop_front();                //Remove from Deque
                  minsLeft = current.getMins();       //reset Minutes counter
               }
            break;
         }
         case OTHERTEXT:                              //New requests
         {

            cin >> name >> time;                      //Get additional inputs
            int mins = setMins(time);                 //Change string to int
            
            Student next {chooser,name,mins,false};   //Create new student

            if(minsLeft <= 0)                         //Check if we are serving a studnet now
            {
               if(serving.empty())                    //See if anyone else is waiting
               {
                  current = next;                     //If not, may new student current
                  minsLeft = mins;                    //reset Minutes counter
               }
               else                                   //Someone else in Deque
               {
                  current = serving.front();          //Get next student
                  serving.pop_front();                //remove them from Deque
                  minsLeft = current.getMins();       //reset counter
                  serving.push_back(next);            //push new student to Deque
               }
            }
            else                                      //still serving current student
               serving.push_back(next);               // push new student to Deque
            
            break;
         }
         case POUNDPOUND:                             //Emergancy Request
         {
            
            cin >> course >>name >> time;             //Get Addtional inputs
            int mins = setMins(time);                 //Change string to int
            
            Student next {course,name,mins,true};     //Create new student

            if(minsLeft <= 0)                         //Check if we are serving a studnet now
            {
               current = next;                        //If not, may new student current
               minsLeft = mins;                       //reset Minutes counter
            }
            else
               serving.push_front(next);               // push new student to Deque
            
            break;
         }
         case FINISH:                                 //Quit Simulation
         case MAX_VAL:                                //Currently not used
            break;
            
      }
      
      if((picked != FINISH) && minsLeft)              //Display if we aren't finished
      {
        displayInfo(current, minsLeft--);
          
      }
      
      
   }
   while(picked != FINISH);                          //Loop while not Finished
   
   
   // end
   cout << "End of simulation\n";
   
}


/*******************************************
 * string2enum()
 * Function to change input string to output enum
 * for switch statement
 *******************************************/

eChoice string2enum(string word )
{
   for (auto & c: word) c = toupper(c);
   
   if(word == "!!")
      return POUNDPOUND;
   
   if(word == "NONE")
      return NONE;
   
   if(word == "FINISHED")
      return FINISH;
   
   return OTHERTEXT;  //got something else
   
}


/*******************************************
 * displayInfo()
 * Function to display output
 * for switch statement
 *******************************************/
void displayInfo(Student current, const int minsLeft)
{

   if(current.getEmrgcy()) //Current student has an emergancy
   {
      cout << "\tEmergency for ";
   }
   else
   {
      cout << "\tCurrently serving ";
   }
   
   //Print rest of the line
   cout << current.getName()  << " for class " << current.getCourse()
   << ". Time left: " << minsLeft << endl;
   
}

/*******************************************
 * displayInstructions()
 * Function to display instructions
 *******************************************/
void displayInstructions()
{
   
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";
   
}

/*******************************************
 * setMins
 * Change string to integer for minutes
 *******************************************/
int setMins(string time)
{
   int mins = atoi(time.c_str());
   if(mins <= 0)                 //non digit values = 0 from atoi
      mins = 1;
   
   return mins;
   
}

