/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
*    Jeffry Simpson, David Perez 
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

#include "deque.h"     // for DEQUE



/************************************************
 * Student
 * A class that holds our Single Student info
 ***********************************************/
class Student
{
private:
   string m_Course;                    //Student Class
   string m_Name;                      //Student name
   int    m_Mins;                      //Minutes help needed
   bool   m_Emrgcy;                    //Emergancy flag
   
public:
   Student() : m_Course(""), m_Name(""), m_Mins(0), m_Emrgcy(false) {}
   Student(string course, string name, int mins, bool flag )
   {m_Course = course; m_Name = name; m_Mins = mins; m_Emrgcy = flag;}
   
   string getCourse()    { return m_Course;  }
   string getName()      { return m_Name;    }
   int    getMins()      { return m_Mins;    }
   bool   getEmrgcy()    { return m_Emrgcy;  }
   
   void setCourse(string course) { m_Course = course;}
   void setName(string student)  { m_Name = student; }
   void setMins(int minutes)     { m_Mins = minutes; }
   void setEmrgcy(bool value)    { m_Emrgcy = value; }
   
};

//Enum for Menu Swticher
enum eChoice
{
   POUNDPOUND,
   NONE,
   FINISH,
   OTHERTEXT,
   MAX_VAL
};



//Function definiton
void nowServing();
void displayInstructions();
void displayInfo(Student current, const int Mins);
eChoice string2enum(string word );
int setMins(string time);


#endif // NOW_SERVING_H

