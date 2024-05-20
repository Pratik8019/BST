#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure for product information
typedef struct Product {
    int code;
    char name[100];
    float price;
    int amount;
    char dateReceived[11];
    char expirationDate[11];
} Product;

// Node structure for binary search tree
typedef struct TreeNode {
    Product product;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new product
Product createProduct(int code, char* name, float price, int amount, char* dateReceived, char* expirationDate) {
    Product product;
    product.code = code;
    strcpy(product.name, name);
    product.price = price;
    product.amount = amount;
    strcpy(product.dateReceived, dateReceived);
    strcpy(product.expirationDate, expirationDate);
    return product;
}

// Function to create a new tree node
TreeNode* createTreeNode(Product product) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->product = product;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new product into the BST
TreeNode* insertProduct(TreeNode* root, Product product) {
    if (root == NULL) {
        return createTreeNode(product);
    }
    if (strcmp(product.name, root->product.name) < 0) {
        root->left = insertProduct(root->left, product);
    } else {
        root->right = insertProduct(root->right, product);
    }
    return root;
}

// Function to find the minimum value node in the tree
TreeNode* findMin(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
TreeNode* deleteNode(TreeNode* root, int code) {
    if (root == NULL) return root;

    if (code < root->product.code) {
        root->left = deleteNode(root->left, code);
    } else if (code > root->product.code) {
        root->right = deleteNode(root->right, code);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->product = temp->product;
        root->right = deleteNode(root->right, temp->product.code);
    }
    return root;
}

// Function to list expired items in prefix order of their names
void listExpiredItems(TreeNode* root) {
    if (root == NULL) return;

    // Check if the expiration date is in the past
    time_t now;
    time(&now);
    struct tm* expiration = localtime(&now);
    int currentYear = expiration->tm_year + 1900;
    int currentMonth = expiration->tm_mon + 1;
    int currentDay = expiration->tm_mday;

    int expirationYear, expirationMonth, expirationDay;
    sscanf(root->product.expirationDate, "%d/%d/%d", &expirationDay, &expirationMonth, &expirationYear);

    if (expirationYear < currentYear || (expirationYear == currentYear && expirationMonth < currentMonth) ||
        (expirationYear == currentYear && expirationMonth == currentMonth && expirationDay < currentDay)) {
        printf("Code: %d, Name: %s, Price: %.2f, Amount: %d, Date Received: %s, Expiration Date: %s\n",
               root->product.code, root->product.name, root->product.price, root->product.amount,
               root->product.dateReceived, root->product.expirationDate);
    }

    listExpiredItems(root->left);
    listExpiredItems(root->right);
}

// Function to list all items in the BST
void listAllItems(TreeNode* root) {
    if (root == NULL) return;

    printf("Code: %d, Name: %s, Price: %.2f, Amount: %d, Date Received: %s, Expiration Date: %s\n",
           root->product.code, root->product.name, root->product.price, root->product.amount,
           root->product.dateReceived, root->product.expirationDate);

    listAllItems(root->left);
    listAllItems(root->right);
}

// Function to delete all expired items
TreeNode* deleteExpiredItems(TreeNode* root) {
    if (root == NULL) return NULL;

    // Check if the expiration date is in the past
    time_t now;
    time(&now);
    struct tm* expiration = localtime(&now);
    int currentYear = expiration->tm_year + 1900;
    int currentMonth = expiration->tm_mon + 1;
    int currentDay = expiration->tm_mday;

    int expirationYear, expirationMonth, expirationDay;
    sscanf(root->product.expirationDate, "%d/%d/%d", &expirationDay, &expirationMonth, &expirationYear);

    if (expirationYear < currentYear || (expirationYear == currentYear && expirationMonth < currentMonth) ||
        (expirationYear == currentYear && expirationMonth == currentMonth && expirationDay < currentDay)) {
        return deleteNode(root, root->product.code);
    }

    root->left = deleteExpiredItems(root->left);
    root->right = deleteExpiredItems(root->right);

    return root;
}

// Function to handle menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Insert an item\n");
    printf("2. List expired items in prefix order of their names\n");
    printf("3. List all items\n");
    printf("4. Delete an item by code\n");
    printf("5. Delete all expired items\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    TreeNode* root = NULL;
    int choice, code, amount;
    char name[100];
    float price;
    char dateReceived[11];
    char expirationDate[11];

    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter product code: ");
                scanf("%d", &code);
                printf("Enter product name: ");
                scanf("%s", name);
                printf("Enter product price: ");
                scanf("%f", &price);
                printf("Enter amount in stock: ");
                scanf("%d", &amount);
                printf("Enter date received (dd/mm/yyyy): ");
                scanf("%s", dateReceived);
                printf("Enter expiration date (dd/mm/yyyy): ");
                scanf("%s", expirationDate);
                root = insertProduct(root, createProduct(code, name, price, amount, dateReceived, expirationDate));
                break;
            case 2:
                printf("Expired items in prefix order of their names:\n");
                listExpiredItems(root);
                break;
            case 3:
                printf("All items:\n");
                listAllItems(root);
                break;
            case 4:
                printf("Enter product code to delete: ");
                scanf("%d", &code);
                root = deleteNode(root, code);
                break;
            case 5:
                printf("Deleting all expired items...\n");
                root = deleteExpiredItems(root);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
