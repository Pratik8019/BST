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

// Function to insert a new key into the BST
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to create mirror image of the BST
TreeNode* mirror(TreeNode* root) {
    if (root == NULL) return NULL;

    TreeNode* temp = root->left;
    root->left = mirror(root->right);
    root->right = mirror(temp);

    return root;
}

// Function to find a key in the BST
TreeNode* find(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    if (data < root->data) {
        return find(root->left, data);
    }
    return find(root->right, data);
}

// Function to perform non-recursive postorder traversal
void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    StackNode* stack1 = NULL;
    StackNode* stack2 = NULL;
    push(&stack1, root);

    while (!isStackEmpty(stack1)) {
        TreeNode* current = pop(&stack1);
        push(&stack2, current);

        if (current->left) push(&stack1, current->left);
        if (current->right) push(&stack1, current->right);
    }

    while (!isStackEmpty(stack2)) {
        TreeNode* current = pop(&stack2);
        printf("%d ", current->data);
    }
}

// Function to display the menu and handle user inputs
void menu() {
    TreeNode* root = NULL;
    int choice, key;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Mirror Image\n");
        printf("3. Find\n");
        printf("4. Postorder Traversal (Non-recursive)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                root = mirror(root);
                printf("Mirror image created.\n");
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                TreeNode* foundNode = find(root, key);
                if (foundNode) {
                    printf("Key %d found in the BST.\n", key);
                } else {
                    printf("Key %d not found in the BST.\n", key);
                }
                break;
            case 4:
                printf("Postorder Traversal (Non-recursive): ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
