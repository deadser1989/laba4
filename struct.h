#ifndef STRUCT_H
#define STRUCT_H
#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

typedef struct node {
    int data; //����� 
    struct node* next; //��������� �� ���� ����
} node;

typedef struct Stack {
    node* top; // ���� �����
    int size;
} Stack;

node* createNode(int data);
Stack* createStack();
void push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);
int isEmpty(Stack* stack);
int size(Stack* stack);
void freeStack(Stack* stack);
int loadDataFromFileToStack(const char* filename, Stack* stack1, Stack* stack2);
void printStack(node* top);
void loadFromStack(const char* filename);
void insertionSortStack(Stack* stack);
void writeSortedStackToFile(const char* filename, Stack* stack);
int top(Stack* stack);
int loadSingleLineToStack(const char* filename, Stack* stack);
void writeSortedToFile(const char* filename, Stack* stack);

node* createNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "������ ��� ��������� ������\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "������ ��������� ������ ��� �������� �����\n");
        exit(1);
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
 }

void push(Stack* stack, int data) { //+element
    node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode; //����� ���� = �������
    stack->size++; //+������ �����
}

int pop(Stack* stack) {
    if (stack->top == NULL) {
        return -1;
    }
    node* temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

int top(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "���� ����, ���������� �������� ������� �������.\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

int peek(Stack* stack) { //���������� ������� �������
    if (stack->top == NULL) {
        fprintf(stderr, "������: ���� ����\n");
        return -1;
    }
    return stack->top->data; 
}

int isEmpty(Stack* stack) {
    return stack->top == NULL;
}

int size(Stack* stack) {
    return stack->size;
}

void freeStack(Stack* stack) {
    if (stack == NULL) return;
    node* current = stack->top;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    free(stack);
}

void printStack(node* current) {
    if (current == NULL) {
        return;
    }
    printStack(current->next);
    printf(" %d,", current->data); 
}

//////////////////////////////////////////////////////////////////////............................+_______________________


int isNumber(const char* str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    if (*str == '-') {
        str++;
    }
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}


int loadDataFromFileToStack(const char* filename, Stack* stack1, Stack* stack2) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "������ �������� �����.\n");
        return -1;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    //������ ������ �� �����
    for (int i = 0; i < 2; i++) {
        if ((read = getline(&line, &len, file)) != -1) {
            char* token = strtok(line, ",");
            while (token != NULL) {
                while (isspace(*token)) token++; //������� �������
                char* endptr;
                errno = 0;
                long num = strtol(token, &endptr, 10);

                if (errno == 0 && token != endptr && *endptr == '\0') {
                    int data = (int)num;
                    if (i == 0) {
                        push(stack1, data); //������ ����
                    }
                    else {
                        push(stack2, data); //������ ����
                    }
                }
                else {
                    printf("�� �������: %s\n", token);
                }
                token = strtok(NULL, ",");
            }
        }
    }

    free(line);
    fclose(file);
    return 0;
}


void loadFromStack(const char* filename) {
    Stack* stack1 = createStack();
    Stack* stack2 = createStack();
    if (loadDataFromFileToStack(filename, stack1, stack2) != 0) {
        fprintf(stderr, "������ �������� ������ �� �����\n");
        freeStack(stack1);
        freeStack(stack2);
        return;
    }
    printf("���������� �������� ���: ");
    printStack(stack1->top);
    printf("\n");
    printf("���������� ��������������� ���: ");
    printStack(stack2->top);
    printf("\n");
    freeStack(stack1);
    freeStack(stack2);
}

void writeStackToFile(Stack* stack, FILE* file) {
    int size = 0;
    node* current = stack->top;
    while (current != NULL) {//���������� ������ �����
        size++;
        current = current->next;
    }
    int* values = (int*)malloc(size * sizeof(int));//������� ������ ��� �������� ��������
    current = stack->top;

    for (int i = 0; i < size; i++) {
        values[i] = current->data;
        current = current->next;
    }
    for (int i = size - 1; i >= 0; i--) {
        fprintf(file, "%d", values[i]);
        if (i > 0) {
            fprintf(file, ",");
        }
    }
    free(values);
}


void fillStackAndWriteToFile(const char* filename) {
    Stack* stack = createStack();
    char* buffer = NULL;
    size_t bufferSize = 0;

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "������ �������� ����� ��� ������: %s\n", filename);
        freeStack(stack);
        return;
    }

    printf("������� ����� (����� ������ ��� �������):\n");
    ssize_t bytesRead = getline(&buffer, &bufferSize, stdin);
    if (bytesRead == -1) {
        perror("������ ������ �����");
        fclose(file);
        freeStack(stack);
        return;
    }

    char* token = strtok(buffer, " ,");
    while (token != NULL) {
        char* endptr;
        errno = 0;
        long num = strtol(token, &endptr, 10);

        if (errno == 0 && endptr != token && *endptr == '\0') {
            push(stack, (int)num);
        }
        else {
            printf("������������ ����: %s\n", token);
        }
        token = strtok(NULL, " ,");
    }
    //������ � ���� � ���������� �������
    writeStackToFile(stack, file);
    fclose(file);
    printf("����� ������� �������� � ���� %s.\n", filename);
    printf("���������� �����: ");
    //�����
    printStack(stack->top);
    printf("\n");
    freeStack(stack);
    stack = createStack();
    free(buffer);
}

int loadSingleLineToStack(const char* filename, Stack* stack) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "������ �������� �����.\n");
        return -1;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    // ������ ������ ������ ������ �� �����
    if ((read = getline(&line, &len, file)) != -1) {
        char* token = strtok(line, ",");
        while (token != NULL) {
            while (isspace(*token)) token++; // ������� �������
            char* endptr;
            errno = 0;
            long num = strtol(token, &endptr, 10);

            if (errno == 0 && token != endptr && *endptr == '\0') {
                int data = (int)num;
                push(stack, data); // ��������� ������ � ����
            }
            else {
                printf("�� �������: %s\n", token);
            }
            token = strtok(NULL, ",");
        }
    }

    free(line);
    fclose(file);
    return 0;
}






#endif
