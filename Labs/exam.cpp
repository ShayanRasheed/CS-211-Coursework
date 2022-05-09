#include <iostream>

using namespace std;

class A
{
    public:
        A() {cout << "A constructor" << endl;}
        A(const A& param) {cout << "A copy constructor" << endl;}
        virtual ~A() {cout << "A destructor" << endl;}
        void f1() {cout << "f1A ";}
        virtual void f2() {cout << "f2A ";}
};

class B : public A{
    public:
        B() {cout << "B constructor" << endl;}
        virtual ~B() {cout << "B destructor" << endl;}
        void f1() {cout << "f1B " ;}
        void f2() {cout << "f2B " ;}
};

void foo(A* a)
{
    a->f1();
    a->f2();
}

int main()
{
    A *a = new B();
    B b;
    A ab = b;
    foo(a);
    foo(&b);
    foo(&ab);

    delete a;

    return 0;
}