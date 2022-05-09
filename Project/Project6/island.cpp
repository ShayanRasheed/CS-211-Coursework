#include "header.h"

// ******************** STRING NODE FUNCTIONS *****************************

stringNode::stringNode(char s[])
{
  elem = s;
  next = NULL;
}

void stringNode::setElem(char s[])
{
  elem = s;
}

char* stringNode::getElem ()
{
  return elem;
}

void stringNode::setNext (stringNode* n)
{
  next = n;
}

stringNode* stringNode::getNext()
{
  return next;
}

// ****************** STRING LIST FUNCTIONS ******************************

stringList::stringList()
{
  //stringList constructor 
  head = NULL;
}

void stringList::insert (char s1[])
{
  stringNode* tmp = new stringNode (s1);
  
  // this code just inserts the node at the beginning of the list
  tmp->setNext (head);
  head = tmp;
}

void stringList::remove (char s1[])
{
  //removes a specific value
  stringNode* curr = head;
  stringNode* prev = NULL;
  
  while ( ( curr != NULL ) && ( strcmp(curr->getElem(), s1) != 0 ) )
  {
    prev = curr;
    curr = curr->getNext();
  }

  if ( curr == NULL ) // v1 does not exist in list
    return;

  if ( prev == NULL ) // v1 is in first/head node in list
  {
    head = curr->getNext();
    delete curr;
  }
  else
  {
    prev->setNext( curr->getNext() );
    delete curr;
  }
}

void stringList::removeAll ()
{
  //removes all nodes in linked list
  stringNode* current = head;
  stringNode* next = NULL;
 
  while (current != NULL)
  {
    next = current;
    current = current->getNext();
    delete next;
  }

  head = NULL;
}

stringList::~stringList()
{
  //destructor
  removeAll();
}

bool stringList::checkList(char s[])
{
  //checks the list to see if a certain value is in it
  stringNode* curr = head;

  while(curr != NULL)
  {
    if(strcmp(curr->getElem(), s) == 0)
    {
      return true;
    }
  else
    curr = curr->getNext();
  }

  return false;
}

// *************** NODE FUNCTIONS ********************

myNode::myNode (int v1)
{
  //Node constructor, sets elem to a specific value, next is set to NULL
  elem = v1;
  next = NULL;
}
  
myNode::myNode (int v1, myNode* n)
{
  //Constructor with a specific next value
  elem = v1;
  next = n;
}

void myNode::setElem (int e)
{
  elem = e;
}

int myNode::getElem ()
{
  return elem;
}

void myNode::setNext (myNode* n)
{
  next = n;
}

myNode* myNode::getNext()
{
  return next;
}

// ************************ myList FUNCTIONS ***********************

myList::myList()
{
  //myList constructor 
  head = NULL;
}

myList::myList ( const myList &p)
{
 makeCopy (p);       // This code does a Deep Copy
}

// Code to make a copy of a list - doing a Deep Copy
//   This code uses the recursive method of copyNode()
//   copyNode() should be private since it is intended to only
//   be called by makeCopy()
void myList::makeCopy ( const myList &p)
{
 head = NULL;
 copyNode (p.head);
} 
 
void myList::copyNode (myNode* pNode)
{
  if (pNode != NULL)
  {
    copyNode ( pNode->getNext() );

    // insert nodes at the front of the list while returning
    //   from the recursive calls  (adds values to the front
    //   in reverse order - this copies the list on O(n) time
    head = new myNode ( pNode->getElem(), head );
  }
}

// the overloaded assignment operator
//
myList& myList::operator= (const myList& p)
{
 if ( this == &p )   // both operands are the same
   return *this;     //   do nothing, just return

 removeAll();        // Deallocate the existing list

 makeCopy (p);       // Do a deep copy

 return *this;       // allow for "cascading assignments":  a = b = c;
}

// method to print out all of the values in the list
void myList::show()
{
  myNode* tmp = head;
  
  while ( tmp != NULL )
  {
    printf ("%d ", tmp->getElem() );
    tmp = tmp->getNext();
  }
  printf ("\n");
}

void myList::show2()
{
  //Alternate print function for the travel method
  myNode* tmp = head;
  
  while ( tmp != NULL )
  {
    printf ("%d ", tmp->getElem() );
    if(tmp->getNext() != NULL)
      printf("- ");
    tmp = tmp->getNext();
  }
  printf ("\n");
}

void myList::insert (int v1)
{
  myNode* tmp = new myNode (v1);
  
  // this code just inserts the node at the beginning of the list
  tmp->setNext (head);
  head = tmp;

 }

void myList::insertAtEnd (int v1){
  //Inserts at end of the list
  myNode* curr = head;
  myNode* prev = NULL;

  while(curr != NULL)
  {
    prev = curr;
    curr = curr->getNext();
  }

  myNode* tmp = new myNode(v1);
  
  if(prev == NULL)
  {
    head = tmp;
  }
  else 
  {
    prev->setNext(tmp);
  }
}


void myList::insertInOrder(int v1){
  //Inserts in order or least to greatest int
  myNode* tmp = new myNode (v1);
  myNode* curr = head;
  myNode* prev = NULL;

  while((curr != NULL) && (curr->getElem() < v1))
  {
    prev = curr;
    curr = curr->getNext();
  }
  
  if(head == NULL)
  {
    head = tmp;
  }
  else if(prev == NULL)
  {
    tmp->setNext(head);
    head = tmp;
  }
  else 
  {
    tmp->setNext(curr);
    prev->setNext(tmp);
  }

}

void myList::remove (int v1)
{
  //removes a specific value
  myNode* curr = head;
  myNode* prev = NULL;
  
  while ( ( curr != NULL ) && ( curr->getElem() != v1 ) )
  {
    prev = curr;
    curr = curr->getNext();
  }

  if ( curr == NULL ) // v1 does not exist in list
    return;

  if ( prev == NULL ) // v1 is in first/head node in list
  {
    head = curr->getNext();
    delete curr;
  }
  else
  {
    prev->setNext( curr->getNext() );
    delete curr;
  }
}

void myList::removeFirst()
{
  //removes the first item in the list
  myNode* curr = head;
  head = curr->getNext();
  delete curr;
}

void myList::removeAll ()
{
  //removes all nodes in linked list
  myNode* current = head;
  myNode* next = NULL;
 
  while (current != NULL)
  {
    next = current;
    current = current->getNext();
    delete next;
  }

  head = NULL;
}

myList::~myList()
{
  //destructor
  removeAll();
}


int myList::getListLength(){
  //returns the length of the linked list
  int count = 0;
  myNode* current = head;

  while(current != NULL)
  {
    count++;
    current = current->getNext();
  }

  return count;
}


int myList::getNthElem(int n){
  //returns the elem at a specific index in the linked list
  myNode* curr = head;
  int i = 0;

  while((curr != NULL) && (i <= n))
  {
    if(i == n)
    {
      return curr->getElem();
    }
    curr = curr->getNext();
    i++;
  }

  if(curr == NULL)
    return 0;
  
}

bool myList::checkList(int n)
{
  //checks the list to see if a certain value is in it
  myNode* curr = head;

  while(curr != NULL)
  {
    if(curr->getElem() == n)
    {
      return true;
    }
    else
      curr = curr->getNext();
  }

  return false;
}

bool myList::isEmpty()
{
  //checks if the list is empty
  if(head == NULL)
    return true;
  else
    return false;
}

// **************************** ISLAND FUNCTIONS **************************

island::island()
{
    //Constructor
    visited = -1;
}

//Getter and Setter for visited
void island::setVisited(int n)
{
    visited = n;
}

int island::getVisited()
{
    return visited;
}

//Accesses the getNthElem function for the adjacency list
int island::getAdjValue(int index)
{
    return adjacency.getNthElem(index);
}

//Insert and remove functions for the adjacency list
void island::insertTrip(int newTrip)
{
    adjacency.insertAtEnd(newTrip);
}

void island::removeTrip(int removed)
{
    adjacency.remove(removed);
}

//Prints the adjacency list
void island::printAdj()
{
    adjacency.show();
}

//Prints the length of the adjacency list
int island::adjLength()
{
    return adjacency.getListLength();
}

//Checks the adjacency list for a specific value
bool island::checkIsland(int n)
{
    return adjacency.checkList(n);
}

//Island destructor
island::~island()
{
    adjacency.removeAll();
}