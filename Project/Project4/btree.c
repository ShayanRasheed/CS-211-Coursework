#include "header.h"

void initTree(treeNode** node, char* input)
{
    // Initialzes a Tree Node with both children set to Null

    *node = (treeNode*)malloc(sizeof(treeNode));
    (*node)->left = NULL;
    (*node)->right = NULL;
    (*node)->token = input;
}

void printInfix(treeNode* node)
{
    // Prints out a binary tree with the Infix method

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
    // Prints out a binary tree with the Postfix method

    if (node == NULL) 
        return; 
   
    printPost(node->left); 
  
    printPost(node->right); 
  
    printf("%s ", node->token); 
}

void printPrefix(treeNode* node)
{
    // Prints out a binary tree with the Prefix method

    if (node == NULL) 
          return; 
  
    printf("%s ", node->token);   
  
    printPrefix(node->left);   
  
    printPrefix(node->right); 
}

void clearTree(treeNode* root)
{
    // Frees all nodes in the tree
    if(root == NULL)
        return;
    clearTree(root->right);
    clearTree(root->left);
    free(root);
    return;
}

int evalExpression(treeNode* root)
{
    // Function used to evaluate the expression given by user
    
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