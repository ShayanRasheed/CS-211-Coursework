#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct TreeNode {
	int val; 
	struct TreeNode *left; 
	struct TreeNode *right; 
}node; 

/*Task 1 - Complete the function below,
  newNode() will return a tree node*/
node* newNode(int key){
	node* new = (node*)malloc(sizeof(node));
	new->val = key;
	new->left = NULL;
	new->right = NULL;
	return new;
}

/*Task 2 - Complete the function below to return
the size (number of elements stored) of a binary 
tree*/
int size(node* root){
	if(root == NULL)
	{
		return 0;
	} 

	return 1 + size(root->left) + size(root->right);
}


/*Task 3 - Complete the function below to print 
a binary tree while performing an Preorder traversal.
Recall preorder traversal: 
	visit parent
	visit left subtree
	visit right subtree
you MUST use recursion	*/

void printPreorder(node* r){
	if (r == NULL) 
        return;  
    printf("%d ", r->val);   

    printPreorder(r->left);   
  
    printPreorder(r->right); 
}


/*Task 4 - Complete the function below to print 
a binary tree while performing an Inorder traversal.
Recall inorder traversal: 
	visit left subtree
	visit parent
	visit right subtree
you MUST use recursion	*/

void printInorder(node* r){
	if (r == NULL) 
        return; 
  
    printInorder(r->left); 
  
    printf("%d ", r->val);   
  
    printInorder(r->right);	
}



/*
  Task 5 - Complete the function below to clear a 
  binary tree. Perform a recursive traversal of a
  tree destroying all nodes.
*/

void clearTree(node* root){
	if (root == NULL)
	{
		return; 
	}
  
    clearTree(root->left); 
    clearTree(root->right); 
    
    free(root); 
}

/*
  Task 6 - Complete the function below to find and
  return the max depth of a binary tree. 
  We define max depth of a tree as number of 
  nodes along the longest path from the root node 
  down to the farthest leaf node.
*/
int maxDepth (node* root){
	if (root == NULL)
        return -1;
    else {
        
        int dLeft = maxDepth(root->left);
        int dRight = maxDepth(root->right);
 
        if (dLeft > dRight)
		{
            return (dLeft + 1);
		}
        else
		{
            return (dRight + 1);
		}
    }
}

/*
  Task 7 - Complete the function below to create 
  an ordered binary tree (bst). In a binary search 
  tree, for every node, all nodes in the left subtree
  are smaller while all nodes in the right subtree are
  larger. (You should compare the key with current value
  then decide whether to move to the left or right subtree)
*/

node* insertBST(node* root, int key) 
{ 
    if (root ==NULL)
    {
        root = newNode(key);
    }
    else
    {
        if (root->val > key)
        {
            root->left = insertBST(root->left, key);
        }
        else
        {
            root->right = insertBST(root->right, key);
        }
    }
    return root;
} 