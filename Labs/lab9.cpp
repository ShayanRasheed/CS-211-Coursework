#include <cstdio>
#include <cstdlib>


class Date
{
 private:
   int month;
   int day;
   int year;

 public:
   Date ();
   Date(int month,int day, int year);
   char* toStr (char* buf);
   int getDay();
   int getMonth();
   int getYear();
   void setDay(int d);
   void setMonth(int m);
   void setYear(int y);
   bool sameDay(Date d2);

};

// This class does not have any real constructors (yet)
/*Task 1 - Complete the default constructor,
  Date() will set the date to January 1st, 2000*/
  Date:: Date ()
  {
    day = 1;
    month = 1;
    year = 2000;
  }

  /*Task 2 - Complete the constructor below*/ 

  Date:: Date(int month,int day, int year){
    setMonth(month);
    setMonth(day);
    setYear(year);
  }

  //Getters

  int Date:: getDay(){
    return day; 
  }
  
  /*Task 3: Part a - Complete the getters below*/ 
  int Date:: getMonth(){
    return month;
  }
  int Date:: getYear(){
    return year;
  }

  //Setters

  void Date:: setDay ( int d )
   {
    static int MaxDayCount[] = {0, 31, 28, 31, 30, 31, 30,
      31, 31, 30, 31, 30, 31 };

    if ( month >= 1 && month <= 12 && d >= 1 &&
        d <= MaxDayCount[month] )
      day = d;
    else
      day = 1;
   }

  /*Task 3 - Complete the setters below*/ 
  

  /*Task 4 - Ensure setMonth is only setting
    valid values for month (1 - 12)*/ 
  void Date:: setMonth ( int m )
  {
    if(m<=12 && m >= 1) 
    {
      month = m;
    }
  }

  /*Task 5 - Ensure setYear is only setting
    valid values for year (2000 - 2020). If the
    passed parameter is XX (two digit value) store
    it as 20XX 
    Example: if y = 20 
             then year = 2020
   */ 

  void Date:: setYear ( int y )
  {
    if(y >= 0 && y <= 20)
    {
      year = 2000 + y;
    }
  }


  /*Task 6 - Complete the sameDay function that
    compares two Dates and returns true if they 
    are the same*/
bool Date:: sameDay(Date d2){
    if(d2.day == day && d2.month == month && d2.year == year)
      return true;
    else 
      return false;
  }


// note this is unsafe since length of buf is never verified
char* Date:: toStr (char* buf)
   {
     static char* Months[] = { "NoMonth", 
        "January",   "February", "March",    "April", 
        "May",       "June",     "July",     "August", 
        "September", "October",  "November", "December" };

     // for MDY format
     //sprintf ( buf, "%s %d, %d", Months[month], day, year );

     // for mm/DD/YYYY format
     sprintf ( buf, "%02d/%02d/%d", month, day, year);

     return buf;
   }


/*Task 7 - Complete the changeDatePBV and changeDatePBA*/ 

// attempt to change the date instance using a Pass-By-Value parameter
void changeDatePBV (Date d)
{
  d.setMonth(12);
  d.setDay(25);
}

// attempt to change the date instance using a Pass-By-ADDRESS parameter
void changeDatePBA (Date *d)
{
  d->setMonth(12);
  d->setDay(25);
}

// This function uses the C++ TRUE Pass-by-Reference parameter syntax
// attempt to change the date instance using a Pass-By-REFERENCE parameter
void changeDatePBR (Date &d)
{
  d.setMonth ( 12 );  // no referencing or dereferencing required!
  d.setDay ( 25 );
}




int main (int argc, char** argv)
{
 char buffer[100];   // buffer of size 100 to print dates

 // create a new instance of the Date class
 Date d; //  the default constructor is called 
 printf ("Default date: %s\n", d.toStr(buffer) );

 Date d2; //  the default constructor is called
 d2.setMonth ( 10 );
 d2.setDay ( 31 );
 d2.setYear ( 20 );
 printf ("Happy Halloween: %s\n", d2.toStr(buffer) );

 // create an instance of Date using the constructor with
 //   three parameters

 Date d3 ( 05, 05, 20 );
 printf ("Last day for CS 211: %s\n", d3.toStr(buffer) ); 


 // Why do CS majors get Halloween and Christmas confused?
 d2.setMonth ( 10 );
 d2.setDay ( 31 );
 d2.setYear ( 20 );
 printf ("Happy Halloween: %s\n", d2.toStr(buffer) );
 changeDatePBV (d2); 
 printf ("PBV Attempt - Merry Christmas?: %s\n", d2.toStr(buffer) );
  
 d2.setMonth ( 10 );
 d2.setDay ( 31 );
 d2.setYear ( 20 );
 printf ("Happy Halloween: %s\n", d2.toStr(buffer) );
 changeDatePBA (&d2); 
 printf ("PBA Attempt - Merry Christmas?: %s\n", d2.toStr(buffer) );
  
 d2.setMonth ( 10 );
 d2.setDay ( 31 );
 d2.setYear ( 20 );
 printf ("Happy Halloween: %s\n", d2.toStr(buffer) );
 changeDatePBR (d2); 
 printf ("PBR Attempt - Merry Christmas?: %s\n", d2.toStr(buffer) );

 Date d4(12,25,2020); 


 if(d2.sameDay(d4)){
  printf("Merry Christmas\n"); 
 }

  
 return 1;
} 
