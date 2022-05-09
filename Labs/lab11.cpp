#include <cstdio>

// The node class for the linked list
//   This contains the operations and data for each individual
//   node in the list.   
//   The "list-level" stuff is maintained in the MyList class
class MyLNode
{
 private:
  int elem;
  MyLNode* next;
  
 public:
  MyLNode (int v1);
  MyLNode (int v1, MyLNode* n);
  
  void setElem (int e);
  int getElem ();
  void setNext (MyLNode* n);
  MyLNode* getNext();
};

// the list class for the linked list
//  This contains all of the operations and data for the
//  list as a whole
//  This class relies heavily on the MyLNode class
class MyList
{
 private:
  MyLNode* head;
  void copyNode (MyLNode* pNode);  
  
 public:
  MyList();              // default constructor
  MyList(const MyList& p); // copy constructor
  ~MyList();             // destructor 
  MyList& operator= ( const MyList& p);  //overloaded assignment operator

  void show();
  void insert(int v1);
  void insertAtEnd(int v1);
  void insertInOrder(int v1);
  void remove (int v1);
  void removeAll ();
  int getListLength();
  int getNthElem(int n);
  void makeCopy (const MyList& p);


};


//  Code for the methods is the MyLNode class
//    These are the Node Level operations
//    Contains: 
//      2 constructors
//      Getters and Setters for the 2 data members
MyLNode::MyLNode (int v1)
{
  elem = v1;
  next = NULL;
}
  
MyLNode::MyLNode (int v1, MyLNode* n)
{
  elem = v1;
  next = n;
}

void MyLNode::setElem (int e)
{
  elem = e;
}

int MyLNode::getElem ()
{
  return elem;
}

void MyLNode::setNext (MyLNode* n)
{
  next = n;
}

MyLNode* MyLNode::getNext()
{
  return next;
}



//  Methods for the MyList class
//    These are the List Level operations
MyList::MyList()
{
  head = NULL;
}

MyList::MyList ( const MyList &p)   //LINE 99
{
 //head = p.head;    // This code does Shallow Copy
 makeCopy (p);       // This code does a Deep Copy
}

// Code to make a copy of a list - doing a Deep Copy
//   This code uses the recursive method of copyNode()
//   copyNode() should be private since it is intended to only
//   be called by makeCopy()
void MyList::makeCopy ( const MyList &p)
{
 head = NULL;
 copyNode (p.head);
} 
 
void MyList::copyNode (MyLNode* pNode)
{
  if (pNode != NULL)
  {
    copyNode ( pNode->getNext() );

    // insert nodes at the front of the list while returning
    //   from the recursive calls  (adds values to the front
    //   in reverse order - this copies the list on O(n) time
    head = new MyLNode ( pNode->getElem(), head );
  }
}

// method to print out all of the values in the list
void MyList::show()
{
  MyLNode* tmp = head;
  
  while ( tmp != NULL )
  {
    printf ("%d, ", tmp->getElem() );
    tmp = tmp->getNext();
  }
  printf ("\n");
}

void MyList::insert (int v1)
{
  MyLNode* tmp = new MyLNode (v1);
  
  // this code just inserts the node at the beginning of the list
  tmp->setNext (head);
  head = tmp;

 }

void MyList::insertAtEnd (int v1){
  MyLNode* curr = head;
  MyLNode* prev = NULL;

  while(curr != NULL)
  {
    prev = curr;
    curr = curr->getNext();
  }

  MyLNode* tmp = new MyLNode(v1);
  
  if(prev == NULL)
  {
    head = tmp;
  }
  else 
  {
    prev->setNext(tmp);
  }
}


void MyList::insertInOrder(int v1){
  MyLNode* tmp = new MyLNode (v1);
  MyLNode* curr = head;
  MyLNode* prev = NULL;

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

void MyList::remove (int v1)
{
  MyLNode* curr = head;
  MyLNode* prev = NULL;
  
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

  

void MyList::removeAll ()
{
  printf("In RemoveAll: \n");
  MyLNode* current = head;
  MyLNode* next = NULL;
 
  while (current != NULL)
  {
    next = current;
    current = current->getNext();
    delete next;
  }

  head = NULL;
}

MyList::~MyList()
{
  printf ("In Destructor: \n");
  // Note that removeAll() does same operation as required by destructor
  removeAll();
 
}

// the overloaded assignment operator
//
MyList& MyList::operator= (const MyList& p)
{
 if ( this == &p )   // both operands are the same
   return *this;     //   do nothing, just return

 removeAll();        // Deallocate the existing list

 makeCopy (p);       // Do a deep copy

 return *this;       // allow for "cascading assignments":  a = b = c;
}

int MyList::getListLength(){
  int count = 0;
  MyLNode* current = head;

  while(current != NULL)
  {
    count++;
    current = current->getNext();
  }

  return count;
}


int MyList::getNthElem(int n){
  MyLNode* curr = head;
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


void functPBR ( MyList &p)
{
 printf ("In functPBR: ");
 p.show();
}

void functPBV ( MyList p)
{
 printf ("In functPBV: ");
 p.show();
}



int main (int argc, char** argv)
{
  MyList list1;
  MyList list2;

  // insert some values
  printf ("\nTesting the insert() and show() methods\n");
  list1.insert (5);
  list1.insert (18);
  list1.insert (10);
  list1.show();
  list1.insert (3);
  list1.show();

  printf ("\nTesting the insertAtEnd() and remove() methods\n");
   
  list2.insertAtEnd (51);
  list2.insertAtEnd (68);
  list2.insertAtEnd (24);
  list2.show();
  list2.remove(22);
  list2.show();
  list2.remove(68);
  list2.show();
  list2.insertAtEnd(12);
    
  // remove some values
  list1.remove (10);
  list1.show();
  list1.remove (7);
  list1.show();
  list1.remove (3);
  list1.show();
  list1.remove (18);
  list1.show();
       
  /* add code to test the getListLength and getNthElem methodes */
  printf ("\nTesting the getListLength() and getNthElem() methods\n");
  MyList list3;
  // insert some values and verify they are correct
  list3.insertInOrder (6);
  list3.insertInOrder (4);
  list3.insertInOrder (10);
  list3.insertInOrder (2);
  list3.insertInOrder (8);
  list3.show();

  int sum = 0;
  for ( int pos = 0 ; pos < list3.getListLength() ; pos++)
   {
       sum = sum + list3.getNthElem( pos );
   }
  printf("The total of the values in the list is: %d\n", sum);


   
  // For the following code, make sure to complete the destructor
  // Code to test the Copy Constructor
  printf ("\nTesting the Copy Constructor\n");
  // creating a nested block of code for a local variable
  if ( true )
  { 
    MyList list4 ( list3 );
    list3.show();
    list4.show();
    list4.insertInOrder(7);
    printf ("If the next 2 lines are the same, Shallow Copy occurred\n");
    list3.show();
    list4.show();

    // as nested block of code ends, destructor will be invoked on list4
  } // LINE 304
    // all of the nodes from list4 were removed
  printf ("\nTesting destructor's impact on list3 for LINE 304 \n");
  list3.show();

  // Test of destructor and Copy Constructor
  printf ("\nTesting the destructor and Copy Constructor LINE 322 and LINE 326\n");
  MyList list5;
  list5.insert (30);
  list5.insert (50);
  list5.insert (10);
  list5.insert (20);
  list5.insert (40);
  list5.show();
  MyList list6;
  list6.makeCopy ( list5 );
  list6.show();
  // call a function sending list5 as pass-by-reference
  functPBR ( list5 );       // LINE 322
  list5.show();

  // call a function sending list6 as pass-by-value
  functPBV ( list6 );       // LINE 326
  list6.show();
  
  // Use the overloaded assignment operator 
  MyList list7, list8, list9;
  list7.insert (3);
  list7.insert (6);
  list7.insert (9);
  list7.insert (12);
  list8.insert (2);
  list8.insert (4);
  list8.insert (6);
  list9.insert (12);
  list9.insert (14);
  list9.insert (16);
  list7.show();
  list8.show();
  list9.show();
  list7 = list8;
  list9 = list9;		// LINE 345
  list7.show();
  list8.show();
  list9.show();
  list7 = list8 = list9;	// LINE 349
  list7.show();
  list8.show();
  list9.show();


  // At End of Main
  printf ("\nAt End of Main: Destructor is invoked\n"); 
 
  return 0;
}
