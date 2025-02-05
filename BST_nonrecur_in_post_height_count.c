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

// Function to perform postorder traversal iteratively
void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    
    Stack stack1, stack2;
    stack1.top = -1;
    stack2.top = -1;
    
    stack1.data[++stack1.top] = root;
    
    while (stack1.top != -1) {
        root = stack1.data[stack1.top--];
        stack2.data[++stack2.top] = root;
        
        if (root->left != NULL)
            stack1.data[++stack1.top] = root->left;
        
        if (root->right != NULL)
            stack1.data[++stack1.top] = root->right;
    }
    
    while (stack2.top != -1) {
        root = stack2.data[stack2.top--];
        printf("%d ", root->data);
    }
}

// Function to calculate height of the tree
int height(TreeNode* root) {
    if (root == NULL) return -1;
    
    Stack stack;
    stack.top = -1;
    int maxHeight = 0;
    int currentHeight = 0;
    TreeNode* lastVisited = NULL;
    
    while (1) {
        while (root != NULL) {
            stack.data[++stack.top] = root;
            root = root->left;
            currentHeight++;
            if (currentHeight > maxHeight)
                maxHeight = currentHeight;
        }
        if (stack.top == -1) break;
        root = stack.data[stack.top];
        if (root->right != NULL && root->right != lastVisited) {
            root = root->right;
        } else {
            lastVisited = stack.data[stack.top--];
            currentHeight--;
            root = NULL;
        }
    }
    
    return maxHeight;
}

// Function to count total number of nodes
int countNodes(TreeNode* root) {
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
            count++;
            root = root->right;
        }
    } while (stack.top != -1 || root != NULL);
    
    return count;
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
       int n, value;
    
    printf("Enter the number of nodes to insert: ");
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        root = insertNode(root, value);
    }

    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inorder Traversal\n");
        printf("2. Postorder Traversal\n");
        printf("3. Height of the Tree\n");
        printf("4. Total Number of Nodes\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                printf("\n");
                break;
            case 2:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 4:
                printf("Total number of nodes: %d\n", countNodes(root));
                break;
            case 5: exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    // Freeing memory allocated for the tree
    freeTree(root);
    
    return 0;
}
