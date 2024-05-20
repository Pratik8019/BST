#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product {
    int code;
    char name[100];
    float price;
    int amount;
    char dateReceived[11];
    char expirationDate[11];
} Product;

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
    } else if (strcmp(product.name, root->product.name) > 0) {
        root->right = insertProduct(root->right, product);
    }
    return root;
}

// Function to find a product by its code
TreeNode* findProduct(TreeNode* root, int code) {
    if (root->product.code == code) {
        return root;
    }
    if (code < root->product.code) {
        return findProduct(root->left, code);
    } else {
        return findProduct(root->right, code);
    }

    return NULL;
}

// Function to update a product
void updateProduct(TreeNode* root, int code, char* name, float price, int amount, char* dateReceived, char* expirationDate) {
    TreeNode* node = findProduct(root, code);
    if (node != NULL) {
        strcpy(node->product.name, name);
        node->product.price = price;
        node->product.amount = amount;
        strcpy(node->product.dateReceived, dateReceived);
        strcpy(node->product.expirationDate, expirationDate);
    } else {
        printf("Product with code %d not found.\n", code);
    }
}

// Inorder traversal to print products in lexicographic order by name
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Code: %d, Name: %s, Price: %.2f, Amount: %d, Date Received: %s, Expiration Date: %s\n",
               root->product.code, root->product.name, root->product.price, root->product.amount,
               root->product.dateReceived, root->product.expirationDate);
        inorderTraversal(root->right);
    }
}

// Function to handle menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Insert a new product\n");
    printf("2. Find and update a product\n");
    printf("3. List all products\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    TreeNode* root = NULL;
    int choice;
    int code, amount;
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
                printf("Enter product code to update: ");
                scanf("%d", &code);
                printf("Enter new product name: ");
                scanf("%s", name);
                printf("Enter new product price: ");
                scanf("%f", &price);
                printf("Enter new amount in stock: ");
                scanf("%d", &amount);
                printf("Enter new date received (dd/mm/yyyy): ");
                scanf("%s", dateReceived);
                printf("Enter new expiration date (dd/mm/yyyy): ");
                scanf("%s", expirationDate);
                updateProduct(root, code, name, price, amount, dateReceived, expirationDate);
                break;
            case 3:
                printf("Products in lexicographic order by name:\n");
                inorderTraversal(root);
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

