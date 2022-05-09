#include "header.h"

void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("or any postfix mathematical expression using operators of *, /, +, -\n");
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
    //Initialize Stack and size variable
    stackNode* top = NULL;
    int size = 0;

    // Use strtok to tokenize the expression
    char* ptr = strtok(expression, " ");
    treeNode* temp;

    while(ptr != NULL)
    {
        //Check if token is an operator
        if(strcmp(ptr, "+") == 0 || strcmp(ptr, "-") == 0 || strcmp(ptr, "*") == 0 || strcmp(ptr, "/") == 0)
        {
            //Initialize a tree node with the operator
            initTree(&temp, ptr);

            //If stack isn't empty, set the right child of the newly created tree node to the top node in the stack
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

            //Do the same for the left child
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
        //If the token is an operand, create a tree node and push it into the stack
        else
        {
            initTree(&temp, ptr);
            push(&top, &temp);
            size++;
        }
        ptr = strtok(NULL, " ");
    }

    //Set the root of the binary tree to the top element of the stack
    treeNode* root;
    if(isEmpty(top) == FALSE)
    {
        root = top->node;
    }

    //If there is more than one element in the Stack or the tree has only one child, return NULL
    if(size > 1 || root->left == NULL)
    {
        clearFull(&top);
        clearTree(top->node);
        free(top);
        return NULL;
    }

    //Free all elements in the stack
    clear(&top);
    free(top);

    return root;
}