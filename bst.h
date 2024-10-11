#pragma once

typedef struct ThreadNode {
	int data;
	struct ThreadNode* right, * left;
	int is_thread;
} ThreadNode;

typedef struct tree_node {
    int data;
    struct tree_node* right, * left;
} TreeNode;

TreeNode* new_node(int key);
TreeNode* insert_node(TreeNode* root, int key);
void inorder_traversal(TreeNode* node);
TreeNode* GenerateBinaryTree(int input[]);
ThreadNode* GenerateThreadTree(int input[]);
ThreadTreeInOrder(ThreadNode* tnode);
ThreadNode* CopyTree(TreeNode* root);

