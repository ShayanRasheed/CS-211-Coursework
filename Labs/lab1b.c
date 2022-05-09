#include <stdio.h>

int main (int argc, char** argv)
{
 
 int val;
 int count = 0;
 int total = 0;

 /* prompt the user for input */
 printf ("Enter in a list of numbers followed by the terminal value of -999\n");
 
 /* loop until the user enters -999 */
 scanf ("%d", &val);
 while (val != -999)
   {
    count++;
    total += val;
    scanf("%d", &val);
   }

 /* calculate the average of the values read in */
 float average = (float)total / count;


 /* display the results */
 /* use the following printf statements to display the results */
 /* remove the comments */

 printf ("For the list of %d numbers with a total of %d\n", count, total);
 printf ("   the average is: %15.5f\n", average);

 return 0;
} 
