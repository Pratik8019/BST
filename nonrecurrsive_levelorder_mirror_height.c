#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct QueueNode {
    TreeNode* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function to create a new tree node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Queue operations
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, TreeNode* node) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQueueNode->node = node;
    newQueueNode->next = NULL;
    if (queue->rear) {
        queue->rear->next = newQueueNode;
    } else {
        queue->front = newQueueNode;
    }
    queue->rear = newQueueNode;
}

TreeNode* dequeue(Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    QueueNode* temp = queue->front;
    TreeNode* node = temp->node;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return node;
}

int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Non-recursive Level Order Traversal
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);
        printf("%d ", current->data);

        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    free(queue);
}

// Non-recursive Mirror Image
void mirror(TreeNode* root) {
    if (root == NULL) return;

    Queue* queue = createQueue();
    enqueue(queue, root);

    while (!isQueueEmpty(queue)) {
        TreeNode* current = dequeue(queue);

        // Swap left and right children
        TreeNode* temp = current->left;
        current->left = current->right;
        current->right = temp;

        if (current->left) enqueue(queue, current->left);
        if (current->right) enqueue(queue, current->right);
    }

    free(queue);
}

// Display height of the tree
int height(TreeNode* root) {
    if (root == NULL) return 0;

    Queue* queue = createQueue();
    enqueue(queue, root);
    int height = 0;

    while (!isQueueEmpty(queue)) {
        int levelSize = 0;
        QueueNode* currentLevel = queue->front;
        while (currentLevel != NULL) {
            levelSize++;
            currentLevel = currentLevel->next;
        }

        for (int i = 0; i < levelSize; i++) {
            TreeNode* current = dequeue(queue);
            if (current->left) enqueue(queue, current->left);
            if (current->right) enqueue(queue, current->right);
        }

        height++;
    }

    free(queue);
    return height;
}

// Helper function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    root->right->right->right = createNode(8);
    root->right->right->right->left = createNode(9);

    return root;
}

int main() {
    TreeNode* root = createSampleTree();

    printf("Level Order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    mirror(root);
    printf("Level Order Traversal of Mirror Image: ");
    levelOrderTraversal(root);
    printf("\n");

    printf("Height of the tree: %d\n", height(root));

    return 0;
}
