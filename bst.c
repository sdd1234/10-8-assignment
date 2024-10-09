#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

TreeNode* new_node(int key) {
    TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
    temp->data = key;
    temp->right = temp->left = NULL;
    return temp;
}

TreeNode* insert_node(TreeNode* root, int key) {
    if (root == NULL)
        return new_node(key);

    if (root->data == key) return root;
    else if (root->data > key) root->left = insert_node(root->left, key);
    else root->right = insert_node(root->right, key);

    return root;
}

void inorder_traversal(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    inorder_traversal(node->left);
    printf("%d ", node->data);
    inorder_traversal(node->right);
}

TreeNode* GenerateBinaryTree(int input[]) {
    TreeNode* root = NULL;

    for (int i = 0; i<15; i++) {
        root = insert_node(root, input[i]);
    }
    return root;
}
int ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;

    while (current != NULL) {
        // 가장 왼쪽 노드로 이동
        while (current->left != NULL && !current->left->is_thread) {
            current = current->left;
        }

        // 현재 노드 방문
        printf("%d ", current->data);

        // 스레드를 따라 이동
        while (current->is_thread) {
            current = current->right;
            printf("%d ", current->data);
        }

        // 오른쪽 서브트리로 이동
        current = current->right;
    }
    return 0;
}


ThreadNode* GenerateThreadTree(int input[]) {
    TreeNode* root = GenerateBinaryTree(input); // GenerateBinaryTree 함수 사용
    ThreadNode* troot = NULL;
    ThreadNode* prev = NULL;

    // 중위 순회를 통해 스레드 트리 생성
    TreeNode* stack[100]; // 스택을 사용하여 중위 순회
    int top = -1;
    TreeNode* current = root;

    while (current != NULL || top != -1) {
        // 가장 왼쪽 노드로 이동
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];

        // 새로운 스레드 노드 생성
        ThreadNode* tnode = (ThreadNode*)malloc(sizeof(ThreadNode));
        if (tnode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        tnode->data = current->data;
        tnode->left = tnode->right = NULL;
        tnode->is_thread = 0;

        if (prev != NULL) {
            prev->right = tnode;
            prev->is_thread = 1;
        }
        else {
            troot = tnode;
        }

        prev = tnode;

        // 오른쪽 서브트리로 이동
        current = current->right;
    }

    // 마지막 노드의 오른쪽 포인터를 NULL로 설정
    if (prev != NULL) {
        prev->right = NULL;
        prev->is_thread = 0;
    }

    return troot;
}




