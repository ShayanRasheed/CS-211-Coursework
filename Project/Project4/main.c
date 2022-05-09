#include "header.h"

int main(int argc, char const *argv[])
{

    char input[300];
  
    /* set up an infinite loop */
    while (1)
    {
        fgets(input,300,stdin);
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
        /* check if user enter ? to see command list */
        else if ( strcmp (input, "?") == 0) 
            printCommands();

        /* user enters an expression */
        else {
            printf ("%s\n", input);

            /* 1- Store the expression in a tree
            2- Display infix notation
            3- Display prefix notation
            4- Display postfix notation
            5- Display the result 
            */

            treeNode* root;
            root = parseExpression(input);

            if(root == NULL)
            {
                printf("Invalid expression. Enter a valid postfix expression \n");
                clearTree(root);
            }
            else
            {
                printf("Infix notation: ");
                printInfix(root);
                printf("\n");

                printf("Prefix notation: ");
                printPrefix(root);
                printf("\n");

                printf("Postfix notation: ");
                printPost(root);
                printf("\n");

                int result = evalExpression(root);
                printf("Expression result: %d \n", result);

                clearTree(root);
            }
        }
    }

    printf ("\nGoodbye\n");
	
	return 0;

}