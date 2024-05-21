#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct StackNode
{
    struct Node *data;
    struct StackNode *next;
};

struct StackNode *createStackNode(struct Node *value)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void push(struct StackNode **top, struct Node *value)
{
    struct StackNode *newNode = createStackNode(value);
    newNode->next = *top;
    *top = newNode;
}

struct Node *pop(struct StackNode **top)
{
    if (*top == NULL)
    {
        return NULL;
    }

    struct StackNode *temp = *top;
    struct Node *poppedValue = temp->data;
    *top = temp->next;
    free(temp);

    return poppedValue;
}

struct Node *insert(struct Node *root, int value)
{
    if (root == NULL)
    {
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    struct Node *current = root;
    struct Node *parent = NULL;

    while (current != NULL)
    {
        parent = current;

        if (value < current->data)
        {
            current = current->left;
        }
        else if (value > current->data)
        {
            current = current->right;
        }
        else
        {
            return root;
        }
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    if (value < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }

    return root;
}

void preorderTraversal(struct Node *root)
{
    if (root == NULL)
        return;

    struct StackNode *stack = NULL;

    while (root != NULL || stack != NULL)
    {
        while (root != NULL)
        {
            printf("%d ", root->data);
            push(&stack, root);
            root = root->left;
        }

        root = pop(&stack);
        root = root->right;
    }
}

void inorderTraversal(struct Node *root)
{
    if (root == NULL)
        return;

    struct StackNode *stack = NULL;

    while (root != NULL || stack != NULL)
    {
        while (root != NULL)
        {
            push(&stack, root);
            root = root->left;
        }

        root = pop(&stack);
        printf("%d ", root->data);
        root = root->right;
    }
}

int countLeafNodes(struct Node *root)
{
    if (root == NULL)
        return 0;

    struct StackNode *stack = NULL;
    int leafCount = 0;

    while (root != NULL || stack != NULL)
    {
        while (root != NULL)
        {
            push(&stack, root);

            if (root->left == NULL && root->right == NULL)
            {
                leafCount++;
            }

            root = root->left;
        }

        root = pop(&stack);
        root = root->right;
    }

    return leafCount;
}

void createMirrorImage(struct Node *root)
{
    if (root == NULL)
        return;

    struct StackNode *stack = NULL;

    while (root != NULL || stack != NULL)
    {
        while (root != NULL)
        {
            push(&stack, root);
            struct Node *temp = root->left;
            root->left = root->right;
            root->right = temp;
            root = root->left;
        }
        root = pop(&stack);
        root = root->right;
    }
}

void displayMirrorImage(struct Node *root)
{
    printf("Mirror Image of the BST:\n");
    inorderTraversal(root);
    printf("\n");
}

int main()
{
    struct Node *root = NULL;
    int value, n;

    printf("Enter the number of nodes to insert in the BST: ");
    scanf("%d", &n);

    printf("Enter the values to insert in the BST:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("Preorder Traversal:\n");
    preorderTraversal(root);
    printf("\n");

    printf("Inorder Traversal:\n");
    inorderTraversal(root);
    printf("\n");

    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));

    createMirrorImage(root);

    displayMirrorImage(root);

    return 0;
}
