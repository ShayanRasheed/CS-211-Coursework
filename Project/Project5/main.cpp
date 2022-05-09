#include "header.h"

void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}

void processExpression (Token inputToken, TokenReader *tr);

int main(int argc, char *argv[])
{
    /***************************************************************/


    Token inputToken;
    TokenReader tr;

    printf ("Starting Expression Evaluation Program\n\n");
    printf ("Enter Expression: ");


    inputToken = tr.getNextToken ();

    while (inputToken.equalsType(QUIT) == false)
    {
      /* check first Token on Line of input */
      if(inputToken.equalsType(HELP))
      {
       printCommands();
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(ERROR))
      {
       printf ("Invalid Input - For a list of valid commands, type ?\n");
       tr.clearToEoln();
      }
      else if(inputToken.equalsType(EOLN))
      {
       printf ("Blank Line - Do Nothing\n");
       /* blank line - do nothing */
      }
      else
      {
       processExpression(inputToken, &tr);
      }

      printf ("\nEnter Expression: ");
      inputToken = tr.getNextToken ();
    }

  printf ("Quitting Program\n");
  return 0;
}

void processExpression (Token inputToken, TokenReader *tr)
{
  /**********************************************/
  /* Declare both stack pointers here      */

  MyStack operatorStack;
  MyStack valueStack;

 /* Loop until the expression reaches its End */
  while (inputToken.equalsType(EOLN) == false)
  {
    /* The expression contain a VALUE */
    if (inputToken.equalsType(VALUE))
      {
        // add code to perform this operation here
        valueStack.push(inputToken.getValue());
      }

    /* The expression contains an OPERATOR */
    else if (inputToken.equalsType(OPERATOR))
      {
        // add code to perform this operation here
        if(inputToken.getOperator() == '(')
        {
          operatorStack.push(inputToken.getOperator());
        }
        else if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-')
        {
          while(operatorStack.isEmpty() == false && (operatorStack.top() == '+' || operatorStack.top() == '-' || operatorStack.top() == '*' || operatorStack.top() == '/' || operatorStack.top() == '%'))
          {
            if(valueStack.getInUse() >= 2)
            {
              operatorStack.popAndEval(valueStack);
            }
            else
            {
              printf("Invalid expression.");
              operatorStack.clear();
              valueStack.clear();
              return;
            }
          }
          operatorStack.push(inputToken.getOperator());
        }
        else if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/' || inputToken.getOperator() == '%')
        {
          while(operatorStack.isEmpty() == false && (operatorStack.top() == '*' || operatorStack.top() == '/' || operatorStack.top() == '%'))
          {
            if(valueStack.getInUse() >= 2)
            {
              operatorStack.popAndEval(valueStack);
            }
            else
            {
              printf("Invalid expression.");
              operatorStack.clear();
              valueStack.clear();
              return;
            }
          }
          operatorStack.push(inputToken.getOperator());
        }
        else if(inputToken.getOperator() == ')')
        {
          while(operatorStack.isEmpty() == false && operatorStack.top() != '(')
          {
            if(valueStack.getInUse() >= 2)
            {
              operatorStack.popAndEval(valueStack);
            }
            else
            {
              printf("Invalid expression.");
              operatorStack.clear();
              valueStack.clear();
              return;
            }
          }
          if(operatorStack.isEmpty() == true)
          {
            printf("Invalid expression.");
            operatorStack.clear();
            valueStack.clear();
            return;
          }
          else
          {
            operatorStack.pop();
          }
        }
      }

      /* get next token from input */
      inputToken = tr->getNextToken ();
    }

  /* The expression has reached its end */

  // add code to perform this operation here
  while(operatorStack.isEmpty() == false)
  {
    operatorStack.popAndEval(valueStack);
  }

  int result = valueStack.topPop();
  if(valueStack.isEmpty() == false)
  {
    printf("Invalid expression.");
    operatorStack.clear();
    valueStack.clear();
    return;
  }
  operatorStack.clear();
  valueStack.clear();
  printf("Expression result: %d\n", result);

  printf ("\n");
}

