// CS 211 Project 7
// Shayan Rasheed
// April 30, 2021
// Dungeon Crawler Game

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;

class tile
{
    private:
        char mazeTile;

    public:
        tile();

        void playerMove();

        char getTile();

        virtual int getGold();

        virtual char* getFile();

        void setTile(char type);

        void printTile();
};

class wall : public tile
{
    public:
        wall();
};

class chest : public tile
{
    private:
        int goldContained;

    public:
        chest(int g);

        int getGold() override;
};

class door : public tile
{
    private:
        char* fileName;

    public:
        door(char* file);

        char* getFile() override;
};

class player
{
    private:
        int gold;
        int tilesVisited;
        int xcurr, ycurr;

    public:
        player();

        void setPos(int x, int y);

        int getX();

        int getY();

        void addGold(int g);

        int getGold();

        void moved(char c);

        int getNumTiles();
};

class room
{
    private:
        tile*** maze;
        player *p;
        int xsize, ysize;
        int xstart, ystart;

    public:
        room(FILE* infile, player* p1);

        void doS();

        void doO();

        void doC();

        void doD();

        void doE();

        void printMaze();

        FILE* playGame();

        void showCommands();

        ~room();
};