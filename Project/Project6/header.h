// CS 211 Project 6
// Shayan Rasheed
// April 8, 2021
// Archipelago Expedition Planner

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

using namespace std;

class stringNode
{
  private:
    char* elem;
    stringNode* next;

  public:
    stringNode(char s[]);
    void setElem (char s[]);
    char* getElem();
    void setNext (stringNode* n);
    stringNode* getNext();
};

class stringList
{
  private:
    stringNode* head;

  public:
  stringList();

  void insert (char s1[]);

  void remove (char s1[]);

  void removeAll ();

  ~stringList();

  bool checkList(char s[]);
};

class myNode
{
  // Node class to be used in myList, holds one int and a pointer to the next node
  private:
    int elem;
    myNode* next;

  public:
    myNode (int v1);
    myNode (int v1, myNode* n);

    void setElem (int e);
    int getElem ();
    void setNext (myNode* n);
    myNode* getNext();
};

class myList
{
  //myList class, holds a pointer to the head node 
  private:
    myNode* head;
    void copyNode (myNode* pNode);  

  public:
    myList();              // default constructor
    myList(const myList& p); // copy constructor
    ~myList();             // destructor 
    myList& operator= ( const myList& p);  //overloaded assignment operator 
    void makeCopy (const myList& p);

    void show();
    void show2();
    void insert(int v1);
    void insertAtEnd(int v1);
    void insertInOrder(int v1);
    void remove (int v1);
    void removeFirst();
    void removeAll ();
    int getListLength();
    int getNthElem(int n);
    bool checkList(int n);
    bool isEmpty();
};

class island
{
  //Island class, holds the adjacency linked list and the previous island visited
  private:
    myList adjacency;
    int visited;

  public:
    island();

    //Getter and Setter for visited
    void setVisited(int n);

    int getVisited();

    //Accesses the getNthElem function for the adjacency list
    int getAdjValue(int index);

    //Insert and remove functions for the adjacency list
    void insertTrip(int newTrip);

    void removeTrip(int removed);

    //Prints the adjacency list
    void printAdj();

    //Prints the length of the adjacency list
    int adjLength();

    //Checks the adjacency list for a specific value
    bool checkIsland(int n);

    //Island destructor
    ~island();
};