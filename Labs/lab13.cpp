#include <cstdio>
#include <cstring>

// The top most class in the hierarchy
class Animal
{
 private:
   char type[30];

 public:
   Animal (char* t)
   {
     strcpy ( type, t );
   }

   char* getType()
   {
     return type;
   }

   void sayHello()
   {
     printf ("Hello.  I am a %s.\n", type);
   }

   virtual void move()		// LINE 26
   {
     printf ("I am moving.\n");
   }

   virtual void say()			// LINE 31
   {
     printf ("I am speaking.\n");
   }
};

// Canine class - subclass of the "parent"/"base" class Animal
class Canine : public Animal
{
 public:

   Canine ( char* t)    // LINE 42
     : Animal (t)       // call the Constructor in parent class
   {  }                 // no body since initialization list does everything

   void move( )  // override  // LINE 46: C++11 allows keyword override
   {
     printf ("I am running.\n");
   }
};

// Dog class - subclass of the "parent"/"base" class Canine
class Dog : public Canine
{
 private:
   int age;

 public:
   Dog ( char* t)     	// LINE 59
     : Canine (t)       // LINE 60 - call the Constructor in parent class
   {  }                 // no body since initialization list does everything

   void say() // override  // C++11 allows keyword override
   {
     printf ("Woof. Woof...Ed..Ward...\n");
   }
};

// Wolf class - subclass of the "parent"/"base" class Canine
class Wolf : public Canine
{
 private:
   int age;

 public:
   Wolf ( char* t)     	// LINE 76 
     : Canine (t)       // call the Constructor in parent class
   {  }                 // no body since initialization list does everything

   void say() // override  // C++11 allows keyword override
   {
     printf ("Winter is coming.\n");
   }
};

// Fox class - subclass of the "parent"/"base" class Canine
class Fox : public Canine
{
 private:
   int age;

 public:
   Fox ( char* t)     	// LINE  93
     : Canine (t)       // call the Constructor in parent class
   {  }                 // no body since initialization list does everything

};

// Bird class - subclass of the "parent"/"base" class Animal
//
//  This class contains an error that you are to uncover for
//  Question 9.  The override keyword of the C++11 Standard
//  would help find this error quickly.
class Bird : public Animal
{
 public:

   Bird ( char* t)    	// LINE 108
     : Animal (t)       // call the Constructor in parent class
   {  }                 // no body since initialization list does everything

   void move( ) // override  // C++11 allows keyword override
   {
     printf ("I am flying.\n");
   }

   void say() override  //override
   { 
     printf ("Tweet. Tweet.\n");
   }
};

void doStuff ( Animal* a )
{
 printf ("\nIn doStuff() with a %s\n", a->getType() );
 a->sayHello();		// LINE 126
 a->move();		// LINE 127
 a->say();		// LINE 128
}

int main ( int argc, char** argv )
{
 char word[30];

 strcpy ( word, "Animal");
 Animal *a = new Animal (word);
 doStuff (a);		// LINE 137

 strcpy ( word, "Dog");
 Dog *d = new Dog (word);
 doStuff (d);		// LINE 141

 strcpy ( word, "Bird");
 Bird *b = new Bird (word);
 doStuff (b);		// Line 145

 a = d;
 doStuff (a);		// LINE 148
 
 a = b;
 doStuff (a);		// LINE 151

 strcpy ( word, "Fox");
 Fox *f = new Fox (word);
 doStuff (f);		// Line 145
 
 return 0;
}

