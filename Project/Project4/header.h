/* include all libraries here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* put any #define statements here */
#define TRUE 1
#define FALSE 0

/* put any structure declarations here */
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

/* list any needed function prototypes here */
void initTree(treeNode** node, char* input);
void printInfix(treeNode* node);
void printPost(treeNode* node);
void printPrefix(treeNode* node);
void push (stackNode** hd, treeNode** newNode);
int isEmpty (stackNode* hd);
treeNode* pop (stackNode** hd);
void clear(stackNode** hd);
void clearTree(treeNode* root);
treeNode* parseExpression(char expression[]);
int evalExpression(treeNode* root);
void printCommands();

