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

// Queue structure for non-recursive postorder traversal
typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, TreeNode* treeNode) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

TreeNode* dequeue(Queue* queue) {
    if (queue->front == NULL) return NULL;
    QueueNode* temp = queue->front;
    TreeNode* treeNode = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return treeNode;
}

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
    
    stack.data[++stack.top] = root;
    
    while (stack.top != -1) {
        root = stack.data[stack.top--];
        printf("%d ", root->data);
        
        if (root->right != NULL)
            stack.data[++stack.top] = root->right;
        
        if (root->left != NULL)
            stack.data[++stack.top] = root->left;
    }
}

// Function to perform postorder traversal iteratively using queue
void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    Stack stack;
    stack.top = -1;

    while (queue->front != NULL) {
        root = dequeue(queue);
        stack.data[++stack.top] = root;

        if (root->left != NULL)
            enqueue(queue, root->left);
        
        if (root->right != NULL)
            enqueue(queue, root->right);
    }

    while (stack.top != -1) {
        root = stack.data[stack.top--];
        printf("%d ", root->data);
    }

    free(queue);
}

// Function to count total number of nodes
int countNodes(TreeNode* root) {
    if (root == NULL) return 0;
    
    Stack stack;
    stack.top = -1;
    int count = 0;
    
    stack.data[++stack.top] = root;
    
    while (stack.top != -1) {
        root = stack.data[stack.top--];
        count++;
        
        if (root->right != NULL)
            stack.data[++stack.top] = root->right;
        
        if (root->left != NULL)
            stack.data[++stack.top] = root->left;
    }
    
    return count;
}

// Function to display leaf nodes
void displayLeafNodes(TreeNode* root) {
    if (root == NULL) return;
    
    Stack stack;
    stack.top = -1;
    
    stack.data[++stack.top] = root;
    
    while (stack.top != -1) {
        root = stack.data[stack.top--];
        
        if (root->left == NULL && root->right == NULL) {
            printf("%d ", root->data);
        }
        
        if (root->right != NULL)
            stack.data[++stack.top] = root->right;
        
        if (root->left != NULL)
            stack.data[++stack.top] = root->left;
    }
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
    insertNode(root, 75);
    insertNode(root, 85);
    
    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");
    
    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");
    
    printf("Total number of nodes: %d\n", countNodes(root));
    
    printf("Leaf nodes: ");
    displayLeafNodes(root);
    printf("\n");
    
    // Freeing memory allocated for the tree
    freeTree(root);
    
    return 0;
}
