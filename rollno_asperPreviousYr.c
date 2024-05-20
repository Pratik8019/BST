#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store student information
typedef struct Student {
    char name[100];
    float score;
    int rollNo;
} Student;

// Node structure for binary search tree
typedef struct TreeNode {
    Student student;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Function to create a new student
Student createStudent(char* name, float score) {
    Student student;
    strcpy(student.name, name);
    student.score = score;
    student.rollNo = 0; // Initially roll number is not assigned
    return student;
}

// Function to create a new tree node
TreeNode* createTreeNode(Student student) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->student = student;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a student into the BST based on score
TreeNode* insertStudent(TreeNode* root, Student student) {
    if (root == NULL) {
        return createTreeNode(student);
    }
    if (student.score > root->student.score) {
        root->left = insertStudent(root->left, student);
    } else {
        root->right = insertStudent(root->right, student);
    }
    return root;
}

// Function to assign roll numbers in ascending order based on scores
void assignRollNumbers(TreeNode* root, int* currentRollNo) {
    if (root != NULL) {
        assignRollNumbers(root->left, currentRollNo);
        root->student.rollNo = (*currentRollNo)++;
        assignRollNumbers(root->right, currentRollNo);
    }
}

// Function to perform inorder traversal and print the students with roll numbers
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Name: %s, Score: %.2f, Roll No: %d\n", root->student.name, root->student.score, root->student.rollNo);
        inorderTraversal(root->right);
    }
}

// Function to handle menu
void menu() {
    printf("\nMenu:\n");
    printf("1. Insert a student\n");
    printf("2. Assign roll numbers and display students\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    TreeNode* root = NULL;
    int choice;
    char name[100];
    float score;

    while (1) {
        menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter student name: ");
                scanf("%s", name);
                printf("Enter student score: ");
                scanf("%f", &score);
                root = insertStudent(root, createStudent(name, score));
                break;
            case 2: {
                int currentRollNo = 1;
                assignRollNumbers(root, &currentRollNo);
                printf("Students with assigned roll numbers:\n");
                inorderTraversal(root);
                break;
            }
            case 3:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}
