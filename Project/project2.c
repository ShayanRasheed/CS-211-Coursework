// CS 211 Project 2
// Shayan Rasheed
// February 14, 2021
// Balanced Symbol Checker

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct StackStruct{
    char* darr;
    int size;
    int inUse;
}Stack;

void init (Stack* s);

int isEmpty (Stack* s);

char top (Stack* s);

void grow (Stack* s);

void push (Stack* s, char opening);

void pop (Stack* s);

void clear (Stack* s);

int isOpening(char input);

int isClosing(char input);

char counterpart(char input);

int main (int argc, char** argv)
{
    // Check to see if debug flag -d was inputted by user

    int debugMode = FALSE;
    for(int k =0; k < argc ; k++)
    {
	    if(strcmp(argv[k], "-d")==0)
        {
		    debugMode = TRUE;
	    }
    }

    char input[301];

    // Declare and Initialize the stack

    Stack myStack;
    init(&myStack);

    /* set up an infinite loop */
    while (1)
    {
        /* get line of input from standard input */
        printf ("\nEnter input to check or q to quit\n");
        fgets(input, 300, stdin);
    
        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0')
        {
            i++;
        }
        input[i] = '\0';

        /* check if user enter q or Q to quit program */
        if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
            break;
 
        /* run the algorithm to determine is input is balanced */

        // Initialize "error" variable that will be swtiched to TRUE once error is detected
        int error = FALSE;
        int m, j;

        // Loop through input given by user
        for(m = 0; m < strlen(input); m++)
        {
            // Check to see if the char is an opening symbol
            if(isOpening(input[m]) == TRUE)
            {
                // If stack is full, the array must be grown
                if(myStack.inUse == myStack.size)
                {
                    grow(&myStack);
                    if(debugMode == TRUE)
                    {
                        printf("Stack size increased from %d to %d, a total of %d values were copied \n", myStack.size-4, myStack.size, myStack.size-4);
                    }
                }
                
                // Push open symbol onto stack
                push(&myStack, input[m]);

                if(debugMode == TRUE)
                {
                    printf("Character %c was pushed into the stack \n", input[m]);
                }
            }

            // Check if the char is a closing symbol
            else if(isClosing(input[m]) == TRUE)
            {
                // If there is a closing symbol while the stack is empty, error 2 occurs
                if(isEmpty(&myStack) == TRUE)
                {
                    error = TRUE;

                    printf("Unbalanced expression. Error 2: missing an opening symbol\n");
                    printf ("%s\n", input);

                    for(j = 0; j < m; j++)
                    {
                        printf(" ");
                    }
                    printf("^ missing %c", counterpart(input[m]));

                    clear(&myStack);
                    break;
                }

                // If the closing symbol does not match the symbol at the top of the stack, error 1 occurs
                else if(counterpart(input[m]) != top(&myStack))
                {
                    error = TRUE;

                    printf("Unbalanced expression. Error 1: expecting a different closing symbol\n");
                    printf ("%s\n", input);

                    for(j = 0; j < m; j++)
                    {
                        printf(" ");
                    }
                    printf("^ expecting %c", counterpart(top(&myStack)));

                    clear(&myStack);
                    break;
                }

                // If closing symbol does match the symbol at the top of the stack, that symbol is removed
                else if(counterpart(input[m]) == top(&myStack))
                {
                    if(debugMode == TRUE)
                    {
                        printf("Character %c was popped from the stack \n", top(&myStack));
                    }

                    pop(&myStack);
                }     
            }
        }

        //If the stack is not empty after the loop, a closing symbol is not present
        if(error == FALSE && isEmpty(&myStack) == FALSE)
        {
            error = TRUE;

            printf("Unbalanced expression. Error 3: missing a closing symbol\n");
            printf ("%s\n", input);

            for(int k = 0; k < i; k++)
            {
                printf(" ");
            }
            printf("^ missing %c", counterpart(top(&myStack)));

            clear(&myStack);
        }

        // If an error has not been detected, the expression is balanced
        if(error == FALSE)
        {
            printf ("%s\n", input);
            printf("Expression is balanced\n"); 

            clear(&myStack);
        }
    }
    
    // Free the allocated memory for the dynamic array
    free(myStack.darr);

    printf ("\nGoodbye\n");
    return 0;
}

void init (Stack* s)
{
    //Initializes a stack with a dynamic array of size 4

    s->size = 4;
    s->darr = (char*)malloc(sizeof(char)*s->size);
    s->inUse = 0;
}

int isEmpty (Stack* s)
{
    // Checks if a stack is empty

    if(s->inUse == 0)
        return TRUE;
    else
        return FALSE;
}

char top (Stack* s)
{
    // Returns the value at the top of the stack

    return (s->darr[s->inUse-1]);
}

void grow (Stack* s)
{
    // Increases the size of the stack by 4

    char *temp;
    temp = s->darr;
    s->darr = (char*)malloc(sizeof(char)*(s->size+4));
        
    for(int j = 0; j < s->size; j++)
    {
        s->darr[j] = temp[j];
    }

    free(temp);

    s->size += 4;
}

void push (Stack* s, char opening)
{
    // adds a char to the stack

    s->darr[s->inUse] = opening;
    s->inUse = s->inUse + 1;
}

void pop (Stack* s)
{
    // Removes the char from the top of the stack

    s->inUse = s->inUse - 1;
}

void clear (Stack* s)
{
    // Resets the stack by freeing it and allocating a new dynamic array of size 4
    free(s->darr);
    init(s);
}

int isOpening(char input)
{
    // Checks to see if a char is an opening bracket

    if(input == '(' || input == '[' || input == '{' || input == '<')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int isClosing(char input)
{
    // Checks to see if a char is a closing bracket

    if(input == ')' || input == ']' || input == '}' || input == '>')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

char counterpart(char input)
{
    // Returns the opposite of any symbol

    if(input == ')')
    {
        return '(';
    }
    else if(input == '}')
    {
        return '{';
    }
    else if(input == ']')
    {
        return '[';
    }
    else if(input == '>')
    {
        return '<';
    }

    if(input == '(')
    {
        return ')';
    }
    else if(input == '{')
    {
        return '}';
    }
    else if(input == '[')
    {
        return ']';
    }
    else if(input == '<')
    {
        return '>';
    }
}