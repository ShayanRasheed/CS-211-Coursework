#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

typedef struct treeNode
{
    struct treeNode* right;
    struct treeNode* left;
    char* token;
}treeNode;

typedef struct stackNode
{
    treeNode* node;
    struct stackNode* next;
}stackNode;

void initTree(treeNode** node, char* input)
{
    *node = (treeNode*)malloc(sizeof(treeNode));
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->token = input;
}

void printInfix(treeNode* node)
{
    if (node == NULL) 
          return; 
  
    if(strcmp(node->token, "+") == 0 || strcmp(node->token, "-") == 0 || strcmp(node->token, "*") == 0 || strcmp(node->token, "/") == 0)
    {
        printf("( ");
    }

    printInfix(node->left); 
  
    printf("%s ", node->token);   
  
    printInfix(node->right);

    if(strcmp(node->token, "+") == 0 || strcmp(node->token, "-") == 0 || strcmp(node->token, "*") == 0 || strcmp(node->token, "/") == 0)
    {
        printf(")");
    }
}

void printPost(treeNode* node)
{
    if (node == NULL) 
        return; 
   
    printPost(node->left); 
  
    printPost(node->right); 
  
    printf("%s ", node->token); 
}

void printPrefix(treeNode* node)
{
    if (node == NULL) 
          return; 
  
    printf("%s ", node->token);   
  
    printPrefix(node->left);   
  
    printPrefix(node->right); 
}

void push (stackNode** hd, treeNode** newNode)
{
    //Pushes an element into the stack

    stackNode* ptr = (stackNode*) malloc (sizeof(stackNode));
    ptr->node = *newNode;
    ptr->next = NULL;
    ptr->next = *hd;
    *hd = ptr;
}

int isEmpty (stackNode* hd)
{
    //Checks if the stack is empty

    if (hd == NULL)
        return TRUE;
    else if(hd->node == NULL)
    {
        return TRUE;
    }
    else
        return FALSE;
}

treeNode* pop (stackNode** hd)
{
    //Removes the top element of the linked list
    stackNode* tmp = *hd;
    treeNode* popped = tmp->node;
    *hd = (*hd)->next;
    free(tmp);
    return popped;
}

void clear(stackNode** hd)
{
    //Pops out all elements in the Linked list
    while((*hd)->next != NULL)
    {
        pop(hd);
    }
}

void clearTree(treeNode* root)
{
    if(root == NULL)
        return;
    clearTree(root->right);
    clearTree(root->left);
    free(root);
    return;
}

void clearFull(stackNode** hd)
{
    //Pops out all elements in the Linked list
    while((*hd)->next != NULL)
    {
        clearTree((*hd)->node);
        pop(hd);
    }
}

treeNode* parseExpression(char expression[])
{
    stackNode* top = NULL;
    int size = 0;
    char* ptr = strtok(expression, " ");
    treeNode* temp;

    while(ptr != NULL)
    {
        if(strcmp(ptr, "+") == 0 || strcmp(ptr, "-") == 0 || strcmp(ptr, "*") == 0 || strcmp(ptr, "/") == 0)
        {
            initTree(&temp, ptr);

            if(isEmpty(top) == FALSE)
            {
                temp->right = pop(&top); 
                size--;
            }
            else
            {
                clearTree(temp);
                return NULL;
            }

            if(isEmpty(top) == FALSE)
            {
                temp->left = pop(&top); 
                size--;
            }
            else
            {
                clearTree(temp);
                return NULL;
            }

            push(&top, &temp);
            size++;
        }
        else
        {
            initTree(&temp, ptr);
            push(&top, &temp);
            size++;
        }
        ptr = strtok(NULL, " ");
    }

    treeNode* root;
    if(isEmpty(top) == FALSE)
    {
        root = top->node;
    }

    if(size > 1 || root->left == NULL)
    {
        clearFull(&top);
        clearTree(top->node);
        free(top);
        return NULL;
    }

    clear(&top);
    free(top);

    return root;
}

int evalExpression(treeNode* root)
{
    if(strcmp(root->token, "+") == 0 || strcmp(root->token, "-") == 0 || strcmp(root->token, "*") == 0 || strcmp(root->token, "/") == 0)
    {
        int lResult = evalExpression(root->left);
        int rResult = evalExpression(root->right);

        if(strcmp(root->token, "+") == 0)
            return lResult + rResult;
        else if(strcmp(root->token, "-") == 0)
            return lResult - rResult;
        else if(strcmp(root->token, "*") == 0)
            return lResult * rResult;
        else if(strcmp(root->token, "/") == 0)
            return lResult / rResult;
    }
    else
    {
        return atoi(root->token);
    }
}

void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("or any postfix mathematical expression using operators of *, /, +, -\n");
}


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
