#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Definition for a binary tree node.
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Stack definition and operations
typedef struct Stack {
    Node* data;
    struct Stack* next;
} Stack;

void push(Stack** top_ref, Node* node) {
    Stack* new_stack_node = (Stack*) malloc(sizeof(Stack));
    if (!new_stack_node) {
        printf("Stack overflow\n");
        exit(0);
    }
    new_stack_node->data = node;
    new_stack_node->next = (*top_ref);
    (*top_ref) = new_stack_node;
}

int isEmpty(Stack* top) {
    return (top == NULL);
}

Node* pop(Stack** top_ref) {
    Node* res;
    Stack* top;

    if (isEmpty(*top_ref)) {
        printf("Stack underflow\n");
        exit(0);
    } else {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}

// Queue definition and operations for height calculation
typedef struct QueueNode {
    Node* node;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, Node* node) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->node = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

Node* dequeue(Queue* q) {
    if (q->front == NULL)
        return NULL;
    QueueNode* temp = q->front;
    Node* node = temp->node;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return node;
}

int isQueueEmpty(Queue* q) {
    return (q->front == NULL);
}

// Binary Tree operations
Node* newNode(int data) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void inorderTraversal(Node* root) {
    Stack* stack = NULL;
    Node* current = root;

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }

        current = pop(&stack);
        printf("%d ", current->data);
        current = current->right;
    }
}

void preorderTraversal(Node* root) {
    Stack* stack = NULL;
    if (root == NULL)
        return;

    push(&stack, root);

    while (!isEmpty(stack)) {
        Node* node = pop(&stack);
        printf("%d ", node->data);

        if (node->right)
            push(&stack, node->right);
        if (node->left)
            push(&stack, node->left);
    }
}

int height(Node* root) {
    if (root == NULL) return 0;

    Queue* queue = createQueue();
    enqueue(queue, root);
    int height = 0;

    while (!isQueueEmpty(queue)) {
        int levelSize = 0;
        QueueNode* currentLevel = NULL;
        while (!isQueueEmpty(queue)) {
            Node* current = dequeue(queue);
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

int findMaximum(Node* root) {
    if (root == NULL)
        return INT_MIN;

    int max = INT_MIN;
    Stack* stack = NULL;
    push(&stack, root);

    while (!isEmpty(stack)) {
        Node* current = pop(&stack);

        if (current->data > max)
            max = current->data;

        if (current->right)
            push(&stack, current->right);
        if (current->left)
            push(&stack, current->left);
    }

    return max;
}

int main() {
    Node* root = newNode(10);
    root->left = newNode(2000);
    root->right = newNode(30);
    root->left->left = newNode(40);
    root->left->right = newNode(500);
    root->right->left = newNode(60);
    root->right->right = newNode(70);
    root->right->right->right = newNode(90);


    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Height of the tree: %d\n", height(root));
    printf("Maximum value in the tree: %d\n", findMaximum(root));

    return 0;
}
