#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Stack structure for non-recursive traversal
typedef struct Stack {
    TreeNode* data[100];
    int top;
} Stack;

// Function to create a new node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into BST
TreeNode* insertNode(TreeNode* root, int data) {
    if (root == NULL)
        return createNode(data);
    
    TreeNode* current = root;
    TreeNode* parent = NULL;
    
    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    
    if (data < parent->data)
        parent->left = createNode(data);
    else
        parent->right = createNode(data);
    
    return root;
}

// Function to perform preorder traversal iteratively
void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    
    Stack stack;
    stack.top = -1;
    
    do {
        while (root != NULL) {
            printf("%d ", root->data);
            if (root->right != NULL)
                stack.data[++stack.top] = root->right;
            root = root->left;
        }
        if (stack.top != -1)
            root = stack.data[stack.top--];
    } while (stack.top != -1 || root != NULL);
}

// Function to perform inorder traversal iteratively
void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    
    Stack stack;
    stack.top = -1;
    
    while (1) {
        while (root != NULL) {
            stack.data[++stack.top] = root;
            root = root->left;
        }
        if (stack.top == -1) break;
        root = stack.data[stack.top--];
        printf("%d ", root->data);
        root = root->right;
    }
}

// Function to count leaf nodes
int countLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;
    
    Stack stack;
    stack.top = -1;
    int count = 0;
    
    do {
        while (root != NULL) {
            stack.data[++stack.top] = root;
            root = root->left;
        }
        if (stack.top != -1) {
            root = stack.data[stack.top--];
            if (root->left == NULL && root->right == NULL)
                count++;
            root = root->right;
        }
    } while (stack.top != -1 || root != NULL);
    
    return count;
}

// Function to mirror the BST
void mirrorImage(TreeNode* root) {
    if (root == NULL) return;
    
    Stack stack;
    stack.top = -1;
    
    do {
        while (root != NULL) {
            TreeNode* temp = root->left;
            root->left = root->right;
            root->right = temp;
            if (root->left != NULL)
                stack.data[++stack.top] = root->left;
            root = root->left;
        }
        if (stack.top != -1)
            root = stack.data[stack.top--];
    } while (stack.top != -1 || root != NULL);
}

// Function to free memory allocated for the tree
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode* root = NULL;
    
    // Inserting nodes into the BST
    root = insertNode(root, 50);
    insertNode(root, 30);
    insertNode(root, 20);
    insertNode(root, 40);
    insertNode(root, 70);
    insertNode(root, 60);
    insertNode(root, 80);
    
    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");
    
    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
    
    printf("Mirror Image (Inorder): ");
    mirrorImage(root);
    inorderTraversal(root);
    printf("\n");
    
    // Freeing memory allocated for the tree
    freeTree(root);
    
    return 0;
}
