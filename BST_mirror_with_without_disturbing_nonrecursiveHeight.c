#include <stdio.h>
#include <stdlib.h>

// Node structure
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Stack structure for non-recursive operations
typedef struct Stack {
    TreeNode* data[100];
    int top;
} Stack;

void push(Stack* stack, TreeNode* node) {
    stack->data[++stack->top] = node;
}

TreeNode* pop(Stack* stack) {
    return stack->data[stack->top--];
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Queue structure for level-order traversal and height calculation
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

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
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
    if (root == NULL) return createNode(data);
    
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else {
        root->right = insertNode(root->right, data);
    }
    
    return root;
}

// Function to find the height of the tree using non-recursive method
int treeHeight(TreeNode* root) {
    if (root == NULL) return 0;

    Queue* queue = createQueue();
    enqueue(queue, root);
    int height = 0;

    while (1) {
        int nodeCount = 0;
        QueueNode* temp = queue->front;

        while (temp != NULL) {
            nodeCount++;
            temp = temp->next;
        }

        if (nodeCount == 0)
            return height;

        height++;

        while (nodeCount > 0) {
            TreeNode* node = dequeue(queue);

            if (node->left != NULL)
                enqueue(queue, node->left);
            if (node->right != NULL)
                enqueue(queue, node->right);
            
            nodeCount--;
        }
    }
}

// Function to display level-order traversal of the tree
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left != NULL)
            enqueue(queue, current->left);

        if (current->right != NULL)
            enqueue(queue, current->right);
    }

    printf("\n");
}

// Function to create a mirror image of the tree
TreeNode* mirrorTree(TreeNode* root) {
    if (root == NULL) return NULL;

    TreeNode* mirror = createNode(root->data);
    mirror->left = mirrorTree(root->right);
    mirror->right = mirrorTree(root->left);

    return mirror;
}

// Function to convert the tree to its mirror image in place
void mirrorTreeInPlace(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirrorTreeInPlace(root->left);
    mirrorTreeInPlace(root->right);
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
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert a node\n");
        printf("2. Display tree level-wise\n");
        printf("3. Display mirror image without disturbing the original tree\n");
        printf("4. Display mirror image by disturbing the original tree\n");
        printf("5. Display height of the tree\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insertNode(root, data);
                break;
            case 2:
                printf("Level-order traversal: ");
                levelOrderTraversal(root);
                break;
            case 3:
                printf("Mirror image without disturbing the original tree: ");
                TreeNode* mirror = mirrorTree(root);
                levelOrderTraversal(mirror);
                freeTree(mirror);
                break;
            case 4:
                printf("Mirror image by disturbing the original tree: ");
                mirrorTreeInPlace(root);
                levelOrderTraversal(root);
                // Restore original tree
                mirrorTreeInPlace(root);
                break;
            case 5:
                printf("Height of the tree: %d\n", treeHeight(root));
                break;
            case 6:
                freeTree(root);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
