#include "header.h"

    MyStack::MyStack()
    {
      darr = new int[2];
      size = 2;
      inUse = 0;
    }

    int MyStack::getInUse()
    {
      return inUse;
    }

    void MyStack::clear()
    {
      delete[] darr;
    }

    bool MyStack::isEmpty ()
    {
    // Checks if a stack is empty

      if(inUse == 0)
        return true;
      else
        return false;
    }

    int MyStack::top ()
    {
      // Returns the value at the top of the stack

      return (darr[inUse-1]);
    }

    void MyStack::grow ()
    {
      // Increases the size of the stack by 4

      int *temp;
      temp = darr;
      darr = new int[size+2];
        
      for(int j = 0; j < size; j++)
      {
        darr[j] = temp[j];
      }

      delete[] temp;

      size += 2;
    }

    void MyStack::push (int pushed)
    {
      // adds to the stack
      if(size == inUse)
        grow();
      darr[inUse] = pushed;
      inUse = inUse + 1;
    }

    void MyStack::pop()
    {
      // Removes the int from the top of the stack

      inUse = inUse - 1;
    }

    int MyStack::topPop()
    {
      int temp = darr[inUse-1];
      inUse = inUse - 1;
      return temp;
    }

    int MyStack::eval(int first, int second, char op)
    {
      if(op == '+')
      {
        return first + second;
      }
      else if(op == '-')
      {
        return first - second;
      }
      else if(op == '*')
      {
        return first * second;
      }
      else if(op == '/')
      {
        return first / second;
      }
      else if(op == '%')
      {
        return first % second;
      }
      else
        return -999;
    }

    void MyStack::popAndEval(MyStack& values)
    {
      char op = topPop();
      int v2 = values.topPop();
      int v1 = values.topPop();
      int v3 = eval(v1, v2, op);
      values.push(v3);
    }