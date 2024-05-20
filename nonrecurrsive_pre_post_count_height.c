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

// Non-recursive Preorder Traversal
void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    StackNode* stack = NULL;
    push(&stack, root);

    while (!isStackEmpty(stack)) {
        TreeNode* current = pop(&stack);
        printf("%d ", current->data);

        if (current->right) push(&stack, current->right);
        if (current->left) push(&stack, current->left);
    }
}

// Non-recursive Postorder Traversal
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

// Count total number of nodes
int countNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int count = 0;
    StackNode* stack = NULL;
    push(&stack, root);

    while (!isStackEmpty(stack)) {
        TreeNode* current = pop(&stack);
        count++;

        if (current->left) push(&stack, current->left);
        if (current->right) push(&stack, current->right);
    }

    return count;
}

// Display height of the tree
int height(TreeNode* root) {
    if (root == NULL) return 0;

    Queue* queue = createQueue();
    enqueue(queue, root);
    int height = 0;

    while (!isQueueEmpty(queue)) {
        int levelSize = 0;
        QueueNode* currentLevel = NULL;
        while (!isQueueEmpty(queue)) {
            TreeNode* current = dequeue(queue);
            if (currentLevel == NULL) {
                currentLevel = (QueueNode*)malloc(sizeof(QueueNode));
                currentLevel->node = current;
                currentLevel->next = NULL;
            } else {
                QueueNode* newLevelNode = (QueueNode*)malloc(sizeof(QueueNode));
                newLevelNode->node = current;
                newLevelNode->next = currentLevel;
                currentLevel = newLevelNode;
            }
            levelSize++;
        }

        while (currentLevel != NULL) {
            QueueNode* currentNode = currentLevel;
            currentLevel = currentLevel->next;
            if (currentNode->node->left) {
                enqueue(queue, currentNode->node->left);
            }
            if (currentNode->node->right) {
                enqueue(queue, currentNode->node->right);
            }
            free(currentNode);
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
    return root;
}

int main() {
    TreeNode* root = createSampleTree();

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("Total number of nodes: %d\n", countNodes(root));

    printf("Height of the tree: %d\n", height(root));

    return 0;
}
