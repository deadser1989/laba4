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
    int data; //числа 
    struct node* next; //указатель на след ухел
} node;

typedef struct Stack {
    node* top; // верх стека
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


node* createNode(int data) {
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "ошибка при выделении памяти\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Ошибка выделения памяти при создании стака\n");
        exit(1);
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
 }

void push(Stack* stack, int data) { //+element
    node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode; //новый узел = вершина
    stack->size++; //+размер стека
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

int peek(Stack* stack) { //посмотреть верхнйи элемент
    if (stack->top == NULL) {
        fprintf(stderr, "Ошибка: стек пуст\n");
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

//////////////////////////////////////////////////////////////////////

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
        fprintf(stderr, "Ошибка открытия файла.\n");
        return -1;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    //читаем строки из файла
    for (int i = 0; i < 2; i++) {
        if ((read = getline(&line, &len, file)) != -1) {
            char* token = strtok(line, ",");
            while (token != NULL) {
                while (isspace(*token)) token++; //удаляем пробелы
                char* endptr;
                errno = 0;
                long num = strtol(token, &endptr, 10);

                if (errno == 0 && token != endptr && *endptr == '\0') {
                    int data = (int)num;
                    if (i == 0) {
                        push(stack1, data); //первый стек
                    }
                    else {
                        push(stack2, data); //второй стек
                    }
                }
                else {
                    printf("не подошло: %s\n", token);
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
        fprintf(stderr, "ошибка загрузки данных из файла\n");
        freeStack(stack1);
        freeStack(stack2);
        return;
    }
    printf("Предыдущий введеный ряд: ");
    printStack(stack1->top);
    printf("\n");
    printf("Предыдущий отсортированный ряд: ");
    printStack(stack2->top);
    printf("\n");
    freeStack(stack1);
    freeStack(stack2);
}


#endif
