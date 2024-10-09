#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main() {
   
    int inputData[] = { 4,1,9,13,15,3,6,14,7,10,12,2,5,8,11 };
    TreeNode* root = GenerateBinaryTree(inputData);
	printf("Binary tree inorder:  ");
    inorder_traversal(root);
    printf("\n");
    
    ThreadNode* troot = GenerateThreadTree(inputData);
    printf("Thread tree inorder:  "); 
    ThreadTreeInOrder(troot);
    free(troot);
    free(root);
  
    return 0;
}
