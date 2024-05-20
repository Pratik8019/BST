/*Write a program to efficiently search a particular employee
record by using Tree data structure. Also sort the data on emp-id
in ascending order. */


#include<stdio.h>
#include<stdlib.h>

struct Employee{
    int emp_id;
    char emp_name[50];
};

struct TreeNode{
    struct Employee data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(struct Employee emp){
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = emp;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* root, struct Employee emp){
    if(root == NULL){
        return createNode(emp);
    }
    if(root->data.emp_id < emp.emp_id){
        root->right = insert(root->right, emp);
    }
    else if(root->data.emp_id > emp.emp_id){
        root->left = insert(root->left, emp);
    }

    return root;
}

struct TreeNode* search(struct TreeNode* root, int emp_id){   
    if(root == NULL || root->data.emp_id == emp_id){
        return root;
    }

    if(emp_id < root->data.emp_id){
        return search(root->left,emp_id);
    }else{
        return search(root->right,emp_id);
    }
}

// void inorderTraversal(struct TreeNode* root){
//     if(root != NULL){
//         inorderTraversal(root->left);
//         printf("Employee id: %d , Employee Name: %s\n", root->data.emp_id,root->data.emp_name);
//         inorderTraversal(root->right);
//     }
// }

struct stack{
    int size;
    int top;
    int *arr;
};

void push(struct stack *s, int x){
    s->top++;
    s->arr[s->top] = x;
}

int pop(struct stack *s){
    if (s->top == -1) {
        printf("Stack Underflow! \n");
        return -1;
    } else {
        int x = s->arr[s->top];
        s->top--;
        return x;
    }
}

int isEmpty(struct stack *s) {
    return s->top == -1;
}

struct stack* createStack(int size) {
    struct stack* stack = (struct Stack*)malloc(sizeof(struct stack));
    stack->size = size;
    stack->top = -1;
    stack->arr = (struct TreeNode**)malloc(size * sizeof(struct TreeNode*));
    return stack;
}

void inorderTraversal(struct TreeNode* root){
    struct TreeNode* current = root;
    struct Stack* stack = createStack(100); // Adjust the size as needed

    while (current != NULL || !isEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }

        current = pop(stack);
        printf("Employee id: %d, Employee Name: %s\n", current->data.emp_id, current->data.emp_name);

        current = current->right;
    }
}

int main(){
    struct TreeNode* root = NULL;
    struct Employee emp;

    // root = insert(root,(struct Employee){1, "Harsh Mahale"});

    int n;
    printf("Enter number of students: ");
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        printf("Enter Roll number: ");
        scanf("%d", &emp.emp_id);
        printf("Enter Name: ");
        scanf("%s", &emp.emp_name);
        root = insert(root,emp);
    }

    int searchEmpID;
    printf("\nEnter the employee ID to search: ");
    scanf("%d", &searchEmpID);
    struct TreeNode* result = search(root, searchEmpID);
    if (result != NULL) {
        printf("Employee with Emp ID %d found! Name: %s\n", result->data.emp_id, result->data.emp_name);
    } else {
        printf("Employee with Emp ID %d not found!\n", searchEmpID);
    }
    printf("\n");
    printf("Sorted Employee Records (by Emp ID):\n");
    inorderTraversal(root);
    return 0;
}