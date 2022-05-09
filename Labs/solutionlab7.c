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
    node* n = (node*) malloc (sizeof(node)); 
    n->val = key;
    n->left = n->right = NULL;   
    return n;
}

/*Task 2 - Complete the function below to return
the size (number of elements stored) of a binary 
tree*/
int size(node* root){
    if(root == NULL)
        return 0;
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
	if(r == NULL)
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
  printPreorder(r->left);
  printf("%d ", r->val );
  printPreorder(r->right);
}



/*
  Task 5 - Complete the function below to clear a 
  binary tree. Perform a recursive traversal of a
  tree destroying all nodes.
*/

void clearTree(node* root){
   
    if(root==NULL) return;  // Nothing to clear
    clearTree(root->left); // Clear left sub-tree
    clearTree(root->right); // Clear right sub-tree
    free(root);    // Destroy this node
    return;
}

/*
  Task 6 - Complete the function below to find and
  return the max depth of a binary tree. 
  Recall that max depth of a tree is the number of 
  nodes along the longest path from the root node 
  down to the farthest leaf node.
*/
int maxDepth (node* root){
    if (root == NULL) 
      return 0 ;
    else
    {
        int lDepth = maxDepth(root->left);
        int rDepth = maxDepth(root->right);
        if(lDepth > rDepth)
            return lDepth +1; 
        else
            return rDepth +1 ;
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
   
    if (root == NULL) 
        return newNode(key); 
  
    if (key < root->val) 
        root->left  = insertBST(root->left, key); 
    else if (key > root->val) 
        root->right = insertBST(root->right, key);    
  
    
    return root; 
    
} 

//use recursion
node* insertBSTR(node* root, int key) 
{ 
    if(root == NULL){
        root = newNode(key);
        return root;
    }
    
    if(key == root->val)
        return root;
    
    if(key < root->val)
        root->left = insertBSTR(root->left, key);
    else
        root->right = insertBSTR(root->right, key);
    
} 



int main(int argc, char const *argv[])
{

	node *root = newNode(5); 
	root->left = newNode(4);
	root->right = newNode(12); 
	root->right->left = newNode(13);
	root->right->right = newNode(2);
	root->left->left = newNode(8);
  root->right->right->right = newNode(6);

  /*           5
             /   \
            4     12
           /     /  \
          8     13   2
                      \
                       6

   preorder: 5 4 8 12 13 2 6
   inorder:  8 4 5 13 12 2 6                   
*/
	printf("Size of the tree is %d\n",size(root));
	printf("Maximum depth of the tree is %d\n", maxDepth(root) );
	printPreorder(root); 
	printf("\n");
	printInorder(root); 
	printf("\n");
  clearTree(root);
  root = NULL;
  printf("Size of the tree is %d\n",size(root));


	
	/*node* bst = NULL; 
	int input ; 
	scanf("%d", &input); 
	while(input != -999){
		bst = insertBST(bst, input); 
		scanf("%d", &input); 
	}

	printInorder(bst);*/
	
	return 0;
}
