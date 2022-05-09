// CS 211 Project 3
// Shayan Rasheed
// March 3, 2021
// Maze Solving

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE  1

// Maze Struct with dynamic array
typedef struct mazeStruct
{
  char **arr;
  int xsize, ysize;
  int xstart, ystart;
  int xend, yend;
} maze;

//Struct for Linked List
typedef struct linkedStruct
{
  int xelem;
  int yelem;
  struct linkedStruct* next;
} linked;

// ****PROTOTYPES****
void init(maze *m);

linked* initLinked(int x, int y, int debug);

void push (linked** hd, int x, int y, int debug);

int isEmpty (linked* hd);

linked top (linked hd);

void pop (linked** hd);

void reset(linked** hd, int debug);

void printInOrder(linked *head);

void show (linked* hd);

int main (int argc, char **argv)
{
  // Check for debug mode
  int debugMode = FALSE;
  for(int k =0; k < argc ; k++)
  {
	  if(strcmp(argv[k], "-d")==0)
    {
		  debugMode = TRUE;
	  }
  }
  
  maze m1;

  int xpos, ypos;
  int i,j;

  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc > 3) {
    printf("Usage: %s <input file name>\n", argv[0]);
    exit(-1);
  }
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[1], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  /* read in the size, starting and ending positions in the maze */

  if(fscanf (src, "%d %d", &m1.xsize, &m1.ysize) == EOF)
  {
    printf("Invalid data file.\n");
    exit(-1);
  }

  if(fscanf (src, "%d %d", &m1.xstart, &m1.ystart) == EOF)
  {
    printf("Invalid data file.\n");
    exit(-1);
  }

  if(fscanf (src, "%d %d", &m1.xend, &m1.yend) == EOF)
  {
    printf("Invalid data file.\n");
    exit(-1);
  }

  /* print them out to verify the input */
  if(m1.xsize < 1 || m1.ysize < 1)
  {
    printf("Maze sizes must be greater than 0.\n");
    exit(-1);
  }
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);

  if(m1.xstart > m1.xsize || m1.ysize > m1.ysize)
  {
    printf("Start/End position outside of maze range.\n");
    exit(-1);
  }
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);

  if(m1.xend > m1.xsize || m1.yend > m1.ysize)
  {
    printf("Start/End position outside of maze range.\n");
    exit(-1);
  }
  printf ("end: %d, %d\n", m1.xend, m1.yend);

  init(&m1);

  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
    for (j = 0; j < m1.ysize+2; j++)
      m1.arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
  {
    m1.arr[i][0] = '*';
    m1.arr[i][m1.ysize+1] = '*';
  }
  for (i=0; i < m1.ysize+2; i++)
  {
    m1.arr[0][i] = '*';
    m1.arr[m1.xsize+1][i] = '*';
  }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
		  
  /*This code will only read the first three lines */
  /*Complete this code by reading the rest of the input
    and placing blocked and coin positions. */
  /* Blocked positions are marked with 'b' in the input file
     They should be marked by * in the maze */
  /*Coin positions are marked by 'c' in the input file
    They should be marked by C in the maze*/

  char type;
  while (fscanf(src,"%d %d %c",&xpos, &ypos, &type) != EOF) 
  {
    if(xpos > m1.xsize || ypos > m1.ysize)
    {
      printf("Invalid coordinates: outside of maze range.\n");
    }
    else if(xpos == m1.xstart && ypos == m1.ystart)
    {
      printf("Invalid coordinates: attempting to block start/end position.\n");
    }
    else if(xpos == m1.xend && ypos == m1.yend)
    {
      printf("Invalid coordinates: attempting to block start/end position.\n");
    }
    else if(type == 'c')
    {
      m1.arr[xpos][ypos] = 'C';
    }    
    else if(type == 'b')
    {
      m1.arr[xpos][ypos] = '*';
    }
    else
      printf("Invalid type: type is not recognized.\n");
  }

  /*Close the file*/
   fclose(src);

  /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
  {
    for (j = 0; j < m1.ysize+2; j++)
      printf ("%c", m1.arr[i][j]);
    printf("\n");
  }
  printf("\n");

  /*Maze Algorithm*/  
  linked *head;
  int coins = 0;

  // Initialize head
  head = initLinked(m1.xstart, m1.ystart, debugMode);

  // Initialize "current" variables to keep track of maze position
  int xcurr = m1.xstart;
  int ycurr = m1.ystart;

  // Set Starting location to "visited"
  m1.arr[m1.xstart][m1.ystart] = 'v';

  while(isEmpty(head) == FALSE)
  {
    // Break out of while loop if end is found
    if(xcurr == m1.xend && ycurr == m1.yend)
    {
      break;
    }

    // Search for Unvisited neighbor
    if(m1.arr[xcurr+1][ycurr] != '*' && m1.arr[xcurr+1][ycurr] != 'v')
    {
      if(m1.arr[xcurr+1][ycurr] == 'C'){
        coins++;
      }
      xcurr += 1;
      push(&head, xcurr, ycurr, debugMode);
      //show(head);
      m1.arr[xcurr][ycurr] = 'v';
    }
    else if(m1.arr[xcurr][ycurr+1] != '*' && m1.arr[xcurr][ycurr+1] != 'v')
    {
      if(m1.arr[xcurr][ycurr+1] == 'C'){
        coins++;
      }
      ycurr += 1;
      push(&head, xcurr, ycurr, debugMode);
      //show(head);
      m1.arr[xcurr][ycurr] = 'v';
    }
    else if(m1.arr[xcurr-1][ycurr] != '*' && m1.arr[xcurr-1][ycurr] != 'v')
    {
      if(m1.arr[xcurr-1][ycurr] == 'C'){
        coins++;
      }
      xcurr -= 1;
      push(&head, xcurr, ycurr, debugMode);
      //show(head);
      m1.arr[xcurr][ycurr] = 'v';
    }
    else if(m1.arr[xcurr][ycurr-1] != '*' && m1.arr[xcurr][ycurr-1] != 'v')
    {
      if(m1.arr[xcurr][ycurr-1] == 'C'){
        coins++;
      }
      ycurr -= 1;
      push(&head, xcurr, ycurr, debugMode);
      //show(head);
      m1.arr[xcurr][ycurr] = 'v';
    }
    else
    {
      // If no unvisited neighbor is found, pop the stack
      if(debugMode == TRUE)
      {
        printf("(%d,%d) popped off the stack.\n", head->xelem, head->yelem);
      }
      pop(&head);
      if(isEmpty(head) == FALSE)
      {
        xcurr = head->xelem;
        ycurr = head->yelem;
      }
      //show(head);
    }
  }

  // If stack is empty, there is no solution
  if(isEmpty(head) == TRUE)
  {
    printf("This maze has no solution.\n");
  }
  else
  {
    printf("The maze has a solution.\n");
    printf("The amount of coins collected: %d\n", coins);
    printf("The path from start to end: \n");

    printInOrder(head);
    printf("\n");
  }
  
  // Free all elements in linked list
  if(isEmpty(head) == FALSE)
  {
    reset(&head, debugMode);
    free(head);
  }

  if(debugMode == TRUE && isEmpty(head) == FALSE)
  {
    printf("(%d,%d) popped off the stack.\n", m1.xstart, m1.ystart);
  }

  // Free the maze
  for(i = 0; i < m1.xsize+2; i++)
  {
    free(m1.arr[i]);
  }
  free(m1.arr);
}


// ****FUNCTION DEFINITIONS****

void init(maze *m)
{
  //Initialized the maze

  m->arr = (char**)malloc(sizeof(char*)*(m->xsize+2));
  for(int i = 0; i < m->xsize+2; i++)
  {
    m->arr[i] = (char*)malloc(sizeof(char)*(m->ysize+2));
  }
}

linked* initLinked(int x, int y, int debug)
{
  //Initializes the linked list

  linked* ptr = (linked*) malloc (sizeof(linked));
  ptr->xelem = x;
  ptr->yelem = y;
  ptr->next = NULL;

  if(debug == TRUE)
  {
    printf("(%d,%d) pushed into the stack.\n", x, y);
  }

  return ptr;
}

void push (linked** hd, int x, int y, int debug)
{
  //Pushes an element into the linked list

  if(debug == TRUE)
  {
    printf("(%d,%d) pushed into the stack.\n", x, y);
  }

  linked* ptr = (linked*) malloc (sizeof(linked));
  ptr->xelem = x;
  ptr->yelem = y;
  ptr->next = *hd;
  *hd = ptr;
}

int isEmpty (linked* hd)
{
  //Checks if the linked list is empty

  if (hd == NULL)
    return TRUE;
  else
    return FALSE;
}

linked top (linked hd)
{
  //returns the top of the linked list
  return (hd);
}

void pop (linked** hd)
{
  //Removes the top element of the linked list
  linked* tmp = *hd;
  *hd = (*hd)->next;
  free(tmp);
}

void reset(linked** hd, int debug)
{
  //Pops out all elements in the Linked list
  while((*hd)->next != NULL)
  {
    if(debug == TRUE)
    {
      printf("(%d,%d) popped off the stack.\n", (*hd)->xelem, (*hd)->yelem);
    }
    pop(hd);
  }
}

void printInOrder(linked *head)
{ 
  // Recursively prints the linked list in order

  if (head == NULL)
  { 
    return; 
  }
  printInOrder(head->next); 
  printf("(%d,%d) ", head->xelem, head->yelem); 
} 

void show (linked* hd)
{
  //Prints out the linked list, used for debugging
  while (hd != NULL)
  {
    printf ("(%d,%d) ", hd->xelem, hd->yelem);
    hd = hd->next;
  }
  printf ("\n");
}