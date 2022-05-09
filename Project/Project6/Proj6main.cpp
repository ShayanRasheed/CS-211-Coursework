#include "header.h"

class ArchipelagoExpedition
{
  private:
    // Create the Data Members for the Archipelago Network here
    island* darr;
    int numIslands;
    stringList files;
  
  public:
  
  // Use a constructor to initialize the Data Members for your expedition
  ArchipelagoExpedition()
  {
    darr = new island[10];
    numIslands = 10;
  }

  //Constructor for a specific value of islands
  ArchipelagoExpedition(int newNum)
  {
    numIslands = newNum;
    darr = new island[newNum];
  }

  //Class destructor
  ~ArchipelagoExpedition()
  {
    for(int i = 0; i < numIslands; i++)
    {
      darr[i].~island();
    }
  }
  
  
  // The main loop for reading in input
  void processCommandLoop (FILE* inFile)
  {
    char  buffer[300];
    char* input;

    input = fgets ( buffer, 300, inFile );   // get a line of input
    
    // loop until all lines are read from the input
    while (input != NULL)
    {
      // process each line of input using the strtok functions 
      char* command;
      command = strtok (input , " \n\t");

      printf ("*%s*\n", command);
    
      if ( command == NULL )
        printf ("Blank Line\n");
 
      else if ( strcmp (command, "q") == 0) 
        return;
     
      else if ( strcmp (command, "?") == 0) 
        showCommands();
     
      else if ( strcmp (command, "t") == 0) 
        doTravel();
     
      else if ( strcmp (command, "r") == 0) 
        doResize();

      else if ( strcmp (command, "i") == 0) 
        doInsert();

      else if ( strcmp (command, "d") == 0) 
        doDelete();

      else if ( strcmp (command, "l") == 0) 
        doList();

      else if ( strcmp (command, "f") == 0) 
        doFile();

      else if ( strcmp (command, "#") == 0) 
        ;
     
      else
        printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }
 
  void showCommands()
  {
    printf ("The commands for this project are:\n");
    printf ("  q \n");
    printf ("  ? \n");
    printf ("  # \n");
    printf ("  t <int1> <int2> \n");
    printf ("  r <int> \n");
    printf ("  i <int1> <int2> \n");
    printf ("  d <int1> <int2> \n");
    printf ("  l \n");
    printf ("  f <filename> \n");
  }

  myList breadthFirstSearch(int x, int y)
  {
    for(int i = 0; i < numIslands; i++)
    {
      darr[i].setVisited(-1);
    }

    myList islandQueue;
    islandQueue.insert(x);

    if(bfs(y, islandQueue) == false)
    {
      printf("You can NOT get from island %d to island %d\n", x, y);
      islandQueue.removeAll();
      return islandQueue;
    }
    else
    {
      printf("You can get from island %d to island %d\n", x, y);
      myList pathList;
      int currentIsland = y;
      pathList.insert(y);
      do{
        currentIsland = darr[currentIsland-1].getVisited();
        pathList.insert(currentIsland);
      }while(currentIsland != x);

      return pathList;
    }
  }

  bool bfs(int b, myList islandQueue)
  {
    while(islandQueue.isEmpty() == false)
    {
      int a = islandQueue.getNthElem(0);
      islandQueue.removeFirst();

      for(int i = 0; i < darr[a-1].adjLength(); i++)
      {
        int c = darr[a-1].getAdjValue(i);

        if(darr[c-1].getVisited() == -1)
        {
          darr[c-1].setVisited(a);
          if(c == b)
            return true;
          islandQueue.insertAtEnd(c);
        }
      }
    }
    return false;
  }
 
  void doTravel()
  {
    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
  
    if ( next == NULL )
    {
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0)
    {
      printf ("Integer value expected\n");
      return;
    }
   
    // get another integer value from the input
    next = strtok (NULL, " \n\t");

  
    if ( next == NULL )
    {
      printf ("Integer value expected\n");
      return;
    }
    val2 = atoi ( next );
    if ( val2 == 0 && strcmp (next, "0") != 0)
    {
      printf ("Integer value expected\n");
      return;
    }
   
    if(val1 > numIslands || val2 > numIslands)
    {
      printf("Invalid value for island\n");
      return;
    }
   
    printf ("Performing the Travel Command from %d to %d\n", val1, val2);

    myList travel = breadthFirstSearch(val1, val2);

    if(travel.isEmpty() == true)
    {
      return;
    }

    printf("shortest path from %d to %d: ", val1, val2 );
    travel.show2();
  }
 
  void doResize()
  {
    //clears all islands and creates a new set of a certain number of islands

    int val1 = 0;

    char* next = strtok (NULL, " \n\t");
  
    if ( next == NULL )
    {
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0)
    {
      printf ("Integer value expected\n");
      return;
    }
   
    printf ("Performing the Resize Command with %d\n", val1 );

    for(int i = 0; i < numIslands; i++)
    {
      darr[i].~island();
    }
    numIslands = val1;
    darr = new island[numIslands];
  }
 
  void doInsert()
  {
    //Inserts the trip from val1 to val2

    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
  
    if ( next == NULL )
    {
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0)
    {
      printf ("Integer value expected\n");
      return;
    }
   
    // get another integer value from the input
    next = strtok (NULL, " \n\t");

  
    if ( next == NULL )
    {
      printf ("Integer value expected\n");
      return;
    }
    val2 = atoi ( next );
    if ( val2 == 0 && strcmp (next, "0") != 0)
    {
      printf ("Integer value expected\n");
      return;
    }

    if(val1 > numIslands || val2 > numIslands)
    {
      printf("Invalid value for island\n");
      return;
    }

    if(val1 == val2)
    {
      printf("Can not add ferry ride to self");
      return;
    }

    printf ("Performing the Insert Command for %d\n", val1 );

    if(darr[val1-1].checkIsland(val2) == true)
    {
      printf("Ferry ride already added!\n");
      return;
    }

    darr[(val1-1)].insertTrip(val2);
  }
 
  void doDelete()
  {
    //Deletes the trip from val1 to val2

    int val1 = 0;
    int val2 = 0;

    // get an integer value from the input
    char* next = strtok (NULL, " \n\t");
  
    if ( next == NULL )
    {
      printf ("Integer value expected\n");
      return;
    }
    val1 = atoi ( next );
    if ( val1 == 0 && strcmp (next, "0") != 0)
    {
      printf ("Integer value expected\n");
      return;
    }
   
    // get another integer value from the input
    next = strtok (NULL, " \n\t");

  
    if ( next == NULL )
    {
      printf ("Integer value expected\n");
      return;
    }
    val2 = atoi ( next );
    if ( val2 == 0 && strcmp (next, "0") != 0)
    {
      printf ("Integer value expected\n");
      return;
    }

    if(val1 > numIslands || val2 > numIslands)
    {
      printf("Invalid value for island\n");
      return;
    }

    if(darr[val1-1].checkIsland(val2) == false)
    {
      printf("Ferry ride does not exist\n");
      return;
    }

    printf ("Performing the Delete Command for %d\n", val1 );

    darr[(val1-1)].removeTrip(val2);
  }
 
  void doList()
  {
    //Prints out adjacency lists of all the islands
    printf ("Displaying the adjacency list:\n" );

    for(int i = 0; i < numIslands; i++)
    {
      printf("%d --> ", i+1);
      darr[i].printAdj();
      printf("\n");
    }
  }

  void doFile()
  {
    // get a filename from the input
    char* fname = strtok (NULL, " \r\n\t");
    if ( fname == NULL )
    {
      printf ("Filename expected\n");
      return;
    }
   
    printf ("Performing the File command with file: %s\n", fname);
   
    // next steps:  (if any step fails: print an error message and return ) 
    //  1. verify the file name is not currently in use
    if(files.checkList(fname) == true)
    {
      printf("File is already in use\n");
      return;
    }
    files.insert(fname);
    //  2. open the file using fopen creating a new instance of FILE*
    FILE* nFile;
    if( (nFile = fopen(fname, "r")) == NULL)
    {
      printf ( "Cannot open the file\n" );
      exit(-1);
    }
    //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
    processCommandLoop(nFile);
    //  4. close the file when processCommandLoop() returns
    fclose(nFile);
    files.remove(fname);
  }
};

int main (int argc, char** argv)
{
  // set up the varqiable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the island adjcency list
  ArchipelagoExpedition islandData;
   
  // call the method that reads and parses the input
  islandData.showCommands();
  printf ("\nEnter commands at blank line\n");
  printf ("    (No prompts are given because of f command)\n");
  islandData.processCommandLoop (inFile);
  
  return 0;
 }