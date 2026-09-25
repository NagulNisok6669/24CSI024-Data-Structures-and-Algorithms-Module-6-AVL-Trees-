//25BAD050 Logapradeep N D
//Module 6_AVL Trees_Q2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int key;
    char code[32];
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node *n) {
    if (n == NULL) return 0;
    return n->height;
}

struct Node* newNode(int key, char* code) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    strcpy(node->code, code);
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node *n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

struct Node* insert(struct Node* node, int key, char* code) {
    if (node == NULL) {
        return newNode(key, code);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, code);
    } else if (key > node->key) {
        node->right = insert(node->right, key, code);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            strcpy(root->code, temp->code);
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(struct Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d %s\n", root->key, root->code);
        inorder(root->right);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct Node *root = NULL;
    for (int i = 0; i < n; i++) {
        int k;
        char c[32];
        scanf("%d %s", &k, c);
        root = insert(root, k, c);
    }

    printf("In-order traversal before deletion:\n");
    inorder(root);

    if (root != NULL) {
        struct Node *minNode = minValueNode(root);
        root = deleteNode(root, minNode->key);
    }

    printf("In-order traversal after deletion:\n");
    inorder(root);

    return 0;
}