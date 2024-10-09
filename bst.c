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
        // ���� ���� ���� �̵�
        while (current->left != NULL && !current->left->is_thread) {
            current = current->left;
        }

        // ���� ��� �湮
        printf("%d ", current->data);

        // �����带 ���� �̵�
        while (current->is_thread) {
            current = current->right;
            printf("%d ", current->data);
        }

        // ������ ����Ʈ���� �̵�
        current = current->right;
    }
    return 0;
}


ThreadNode* GenerateThreadTree(int input[]) {
    TreeNode* root = GenerateBinaryTree(input); // GenerateBinaryTree �Լ� ���
    ThreadNode* troot = NULL;
    ThreadNode* prev = NULL;

    // ���� ��ȸ�� ���� ������ Ʈ�� ����
    TreeNode* stack[100]; // ������ ����Ͽ� ���� ��ȸ
    int top = -1;
    TreeNode* current = root;

    while (current != NULL || top != -1) {
        // ���� ���� ���� �̵�
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }

        current = stack[top--];

        // ���ο� ������ ��� ����
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

        // ������ ����Ʈ���� �̵�
        current = current->right;
    }

    // ������ ����� ������ �����͸� NULL�� ����
    if (prev != NULL) {
        prev->right = NULL;
        prev->is_thread = 0;
    }

    return troot;
}




