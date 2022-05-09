#include "header.h"
// Room Constructor - Takes an input file and player object to set up the maze
room::room(FILE* infile, player* p1)
{
    //Set player data member of room class
    p = p1;

    //Read the size from the file
    if(fscanf (infile, "%d %d", &xsize, &ysize) == EOF)
    {
        printf("Invalid data file.\n");
        exit(-1);
    }

    //Allocate memory for tiles in the maze
    maze = new tile**[xsize+2];
    for(int i = 0; i < xsize+2; i++)
    {
        maze[i] = new tile*[ysize+2];
    }

    //Set all of the tiles within the maze to be regular tiles (not including walls)
    for(int i = 1; i < xsize+1; i++)
    {
        for(int j = 1; j < ysize+1; j++)
            maze[i][j] = new tile();
    }

    //Set the walls of the maze
    for(int i = 0; i < xsize+2; i++)
    {
        maze[i][0] = new wall();
        maze[i][ysize+1] = new wall();
    }

    for(int i = 1; i < ysize+1; i++)
    {
        maze[0][i] = new wall();
        maze[xsize+1][i] = new wall();
    }

    //Create a loop to read from the file
    char  buffer[300];
    char* input;

    input = fgets ( buffer, 300, infile );   // get a line of input

    // loop until all lines are read from the input
    while (input != NULL)
    {
        // process each line of input using the strtok functions
        char* command;
        command = strtok (input , " \n\t");

        printf ("*%s*\n", command);

        //Call the function for the corresponding command
        if ( command == NULL )
            printf ("Blank Line\n");

        else if ( strcmp (command, "S") == 0)
            doS();

        else if ( strcmp (command, "O") == 0)
            doO();

        else if ( strcmp (command, "C") == 0)
            doC();

        else if ( strcmp (command, "D") == 0)
            doD();

        else if ( strcmp (command, "E") == 0)
            doE();

        else if ( strcmp (command, "q") == 0)
        {
            printMaze();
            return;
        }

        else
            printf ("Command is not known: %s\n", command);

        input = fgets ( buffer, 300, infile );   // get the next line of input

        printMaze();
    }

}

void room::doS()
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

    if(val1 < 0 || val2 < 0)
    {
        printf("Enter a positive integer\n");
        return;
    }

    if(val1 > xsize || val2 > ysize)
    {
        printf("Out of Bounds. Try Again.");
        return;
    }

    //Set the starting position of the player for the player object and the maze itself
    p->setPos(val1, val2);
    maze[val1][val2]->setTile('P');
}

void room::doO()
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

    if(val1 < 0 || val2 < 0)
    {
        printf("Enter a positive integer\n");
        return;
    }

    if(val1 > xsize || val2 > ysize)
    {
        printf("Out of Bounds. Try Again.");
        return;
    }

    //Replace the tile object in the maze with the newly created wall
    delete maze[val1][val2];
    maze[val1][val2] = new wall();
}

void room::doC()
{
    int val1 = 0;
    int val2 = 0;
    int val3 = 0;

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

    next = strtok (NULL, " \n\t");


    if ( next == NULL )
    {
        printf ("Integer value expected\n");
        return;
    }
    val3 = atoi ( next );
    if ( val3 == 0 && strcmp (next, "0") != 0)
    {
        printf ("Integer value expected\n");
        return;
    }

    if(val1 < 0 || val2 < 0 || val3 < 0)
    {
        printf("Enter a positive integer\n");
        return;
    }

    if(val1 > xsize || val2 > ysize)
    {
        printf("Out of Bounds. Try Again.");
        return;
    }

    //Replace the tile object in the maze with the newly created chest
    delete maze[val1][val2];
    maze[val1][val2] = new chest(val3);
}

void room::doD()
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

    next = strtok (NULL, " \n\t");

    if ( next == NULL )
    {
        printf ("File Name expected\n");
        return;
    }

    if(val1 < 0 || val2 < 0)
    {
        printf("Enter a positive integer\n");
        return;
    }

    if(val1 > xsize || val2 > ysize)
    {
        printf("Out of Bounds. Try Again.");
        return;
    }

    //Replace the tile object in the maze with the newly created door
    delete maze[val1][val2];
    maze[val1][val2] = new door(next);
}

void room::doE()
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

    if(val1 < 0 || val2 < 0)
    {
        printf("Enter a positive integer\n");
        return;
    }

    if(val1 > xsize || val2 > ysize)
    {
        printf("Out of Bounds. Try Again.");
        return;
    }

    //Set the ending tile
    maze[val1][val2]->setTile('E');
}

void room::printMaze()
{
    //Prints out the maze
    printf("\n");
    for(int i = 0; i < xsize+2; i++)
    {
        for(int j = 0; j < ysize+2; j++)
            maze[i][j]->printTile();
        printf("\n");
    }
    printf("\n");
}

FILE* room::playGame()
{
    //Function that allows user to play the game
    //Create another loop to get user input
    char  buffer[300];
    char* input;

    input = fgets ( buffer, 300, stdin );   // get a line of input

    // loop until all lines are read from the input
    while (input != NULL)
    {
        // process each line of input using the strtok functions
        char* command;
        command = strtok (input , " \n\t");

        printf ("*%s*\n", command);

        if ( command == NULL )
            printf ("Blank Line\n");

        else if ( strcmp (command, "w") == 0)
        {
            tile* move = maze[p->getX()-1][p->getY()];

            if(move->getTile() == '*')
            {
                printf("Invalid move. You have reached a wall/obstacle\n");
            }
            else if(move->getTile() == 'D')
            {
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()-1][p->getY()]->setTile('P');
                p->moved('w');

                printMaze();

                printf("You have reached a door, Moving to the next room\n");
                FILE* src;

                if ( ( src = fopen( move->getFile(), "r" )) == NULL )
                {
                    printf ( "Can't open input file\n" );
                    exit(-1);
                }

                return src;
            }
            else if(move->getTile() == 'C')
            {
                p->addGold(move->getGold());
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()-1][p->getY()]->setTile('P');
                p->moved('w');
                printMaze();
                printf("You have opened a gold chest, earning %d gold coins\n", move->getGold());
            }
            else if(move->getTile() == 'E')
            {
                p->moved('w');
                printf( "Congratulations! You found the exit in %d moves and you collected %d gold coins.\n", p->getNumTiles(), p->getGold());
                return NULL;
            }
            else
            {
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()-1][p->getY()]->setTile('P');
                p->moved('w');
                printMaze();
            }

        }

        else if ( strcmp (command, "a") == 0)
        {
            tile* move = maze[p->getX()][p->getY()-1];

            if(move->getTile() == '*')
            {
                printf("Invalid move. You have reached a wall/obstacle\n");
            }
            else if(move->getTile() == 'D')
            {
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()][p->getY()-1]->setTile('P');
                p->moved('a');

                printMaze();

                printf("You have reached a door, Moving to the next room\n");
                FILE* src;

                if ( ( src = fopen( move->getFile(), "r" )) == NULL )
                {
                    printf ( "Can't open input file\n" );
                    exit(-1);
                }

                return src;
            }
            else if(move->getTile() == 'C')
            {
                p->addGold(move->getGold());
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()][p->getY()-1]->setTile('P');
                p->moved('a');
                printMaze();
                printf("You have opened a gold chest, earning %d gold coins\n", move->getGold());
            }
            else if(move->getTile() == 'E')
            {
                p->moved('a');
                printf( "Congratulations! You found the exit in %d moves and you collected %d gold coins.\n", p->getNumTiles(), p->getGold());
                return NULL;
            }
            else
            {
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()][p->getY()-1]->setTile('P');
                p->moved('a');
                printMaze();
            }
        }

        else if ( strcmp (command, "s") == 0)
        {
            tile* move = maze[p->getX()+1][p->getY()];

            if(move->getTile() == '*')
            {
                printf("Invalid move. You have reached a wall/obstacle\n");
            }
            else if(move->getTile() == 'D')
            {
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()+1][p->getY()]->setTile('P');
                p->moved('s');

                printMaze();

                printf("You have reached a door, Moving to the next room\n");
                FILE* src;

                if ( ( src = fopen( move->getFile(), "r" )) == NULL )
                {
                    printf ( "Can't open input file\n" );
                    exit(-1);
                }

                return src;
            }
            else if(move->getTile() == 'C')
            {
                p->addGold(move->getGold());
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()+1][p->getY()]->setTile('P');
                p->moved('s');
                printMaze();
                printf("You have opened a gold chest, earning %d gold coins\n", move->getGold());
            }
            else if(move->getTile() == 'E')
            {
                p->moved('s');
                printf( "Congratulations! You found the exit in %d moves and you collected %d gold coins.\n", p->getNumTiles(), p->getGold());
                return NULL;
            }
            else
            {
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()+1][p->getY()]->setTile('P');
                p->moved('s');
                printMaze();
            }
        }

        else if ( strcmp (command, "d") == 0)
        {
            tile* move = maze[p->getX()][p->getY()+1];

            if(move->getTile() == '*')
            {
                printf("Invalid move. You have reached a wall/obstacle\n");
            }
            else if(move->getTile() == 'D')
            {
                p->moved('d');
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()][p->getY()+1]->setTile('P');

                printMaze();

                printf("You have reached a door, Moving to the next room\n");
                FILE* src;

                if ( ( src = fopen( move->getFile(), "r" )) == NULL )
                {
                    printf ( "Can't open input file\n" );
                    exit(-1);
                }

                return src;
            }
            else if(move->getTile() == 'C')
            {
                p->addGold(move->getGold());
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()][p->getY()+1]->setTile('P');
                p->moved('d');
                printMaze();
                printf("You have opened a gold chest, earning %d gold coins\n", move->getGold());
            }
            else if(move->getTile() == 'E')
            {
                p->moved('d');
                printf( "Congratulations! You found the exit in %d moves and you collected %d gold coins.\n", p->getNumTiles(), p->getGold());
                return NULL;
            }
            else
            {
                maze[p->getX()][p->getY()]->setTile('.');
                maze[p->getX()][p->getY()+1]->setTile('P');
                p->moved('d');
                printMaze();
            }
        }

        else if ( strcmp (command, "h") == 0)
        {
            showCommands();
            printMaze();
        }

        else if ( strcmp (command, "g") == 0)
        {
            printf("Your score is %d\n", p->getGold());
            printMaze();
        }

        else if ( strcmp (command, "q") == 0)
        {
            return NULL;
        }

        else
            printf ("Invalid command. Type ‘h’ for help");

        input = fgets ( buffer, 300, stdin );   // get the next line of input
    }
}

//Shows the room commands
void room::showCommands()
{
    printf ("The commands for this project are:\n");
    printf ("  q \n");
    printf ("  w \n");
    printf ("  a \n");
    printf ("  s \n");
    printf ("  d \n");
    printf ("  g \n");
}

//Room destructor
room::~room()
{
    for(int i = 0; i < xsize+2; i++)
    {
        for(int j = 0; j < ysize+2; j++)
            delete maze[i][j];
    }
}