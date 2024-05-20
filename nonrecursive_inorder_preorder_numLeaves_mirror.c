#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* node;
    struct StackNode* next;
} StackNode;

// Function to create a new tree node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Stack operations
void push(StackNode** top, TreeNode* node) {
    StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
    newStackNode->node = node;
    newStackNode->next = *top;
    *top = newStackNode;
}

int isStackEmpty(StackNode* top) {
    return top == NULL;
}

TreeNode* pop(StackNode** top) {
    if (isStackEmpty(*top)) {
        return NULL;
    }
    StackNode* temp = *top;
    *top = (*top)->next;
    TreeNode* poppedNode = temp->node;
    free(temp);
    return poppedNode;
}

// Non-recursive Inorder Traversal
void inorderTraversal(TreeNode* root) {
    StackNode* stack = NULL;
    TreeNode* current = root;

    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

// Non-recursive Preorder Traversal
void preorderTraversal(TreeNode* root) {
    StackNode* stack = NULL;
    push(&stack, root);

    while (!isStackEmpty(stack)) {
        TreeNode* current = pop(&stack);
        printf("%d ", current->data);

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
}

// Function to display the number of leaf nodes in the tree
int countLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    StackNode* stack = NULL;
    push(&stack, root);
    int count = 0;

    while (!isStackEmpty(stack)) {
        TreeNode* current = pop(&stack);

        if (current->left == NULL && current->right == NULL) {
            count++;
        }

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }

    return count;
}

// Function to create mirror image of the tree
void mirror(TreeNode* root) {
    StackNode* stack = NULL;
    push(&stack, root);

    while (!isStackEmpty(stack)) {
        TreeNode* current = pop(&stack);

        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
}

int main() {
    // Creating the binary tree
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));

    printf("Mirror Image: \n");
    mirror(root);
    printf("Inorder Traversal of Mirror Image: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
