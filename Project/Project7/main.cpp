#include "header.h"

//Tile Constructor
tile::tile()
{
    mazeTile = '.';
}

//Sets Tile to P
void tile::playerMove()
{
    mazeTile = 'P';
}

//Returns the tile
char tile::getTile()
{
    return mazeTile;
}

//Virtual method for the chest class
int tile::getGold()
{
    return 0;
}

//Virtual method for the door class
char* tile::getFile()
{
    return NULL;
}

//Setter for the tile
void tile::setTile(char type)
{
    mazeTile = type;
}

//Used to print the maze
void tile::printTile()
{
    printf("%c ", mazeTile);
}

//Wall class constructor
wall::wall()
{
    setTile('*');
}

//Chest class constructor
chest::chest(int g)
{
    setTile('C');
    goldContained = g;
}

//Method to Override and return gold
int chest::getGold()
{
    return goldContained;
}

//Door class constructor
door::door(char* file)
{
    setTile('D');
    fileName = file;
}

//Method to override and return file name
char* door::getFile()
{
    return fileName;
}

//Constructor for player class
player::player()
{
    gold = 0;
    tilesVisited = 0;
}

//Sets the position of the player
void player::setPos(int x, int y)
{
    xcurr = x;
    ycurr = y;
}

//Getter methods for X and Y position
int player::getX()
{
    return xcurr;
}

int player::getY()
{
    return ycurr;
}

//Adds to the gold collected when a chest tile is visited
void player::addGold(int g)
{
    gold += g;
}

//returns the gold value
int player::getGold()
{
    return gold;
}

//Increments the tiles visited and updates the player's position
void player::moved(char c)
{
    tilesVisited += 1;

    if(c == 'w')
    {
        xcurr -= 1;
    }
    else if(c == 'a')
    {
        ycurr -= 1;
    }
    else if(c == 's')
    {
        xcurr += 1;
    }
    else if(c == 'd')
    {
        ycurr += 1;
    }
}

//Returns the number of tiles visited
int player::getNumTiles()
{
    return tilesVisited;
}

int main (int argc, char** argv)
{
    FILE* infile = stdin;

    //Attempt to open file
    if ( ( infile = fopen( argv[1], "r" )) == NULL )
    {
        printf ( "Can't open input file: %s", argv[1] );
        exit(-1);
    }

    //Call room constructor and create a player object
    player* p1 = new player();
    room mazeData(infile, p1);

    FILE* src;

    //Lets user play the maze game
    src = mazeData.playGame();

    //Continue to make new mazes and play the game until end is reached
    while(src != NULL)
    {
        room newMaze(src, p1);
        src = newMaze.playGame();
    }

    delete p1;
    return 0;
}