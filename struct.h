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
void insertionSortStack(Stack* stack);
void writeSortedStackToFile(const char* filename, Stack* stack);
int top(Stack* stack);
int loadSingleLineToStack(const char* filename, Stack* stack);
void writeSortedToFile(const char* filename, Stack* stack);

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

int top(Stack* stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "Стек пуст, невозможно получить верхний элемент.\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
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

void writeStackToFile(Stack* stack, FILE* file) {
    int size = 0;
    node* current = stack->top;
    while (current != NULL) {//определяем размер стека
        size++;
        current = current->next;
    }
    int* values = (int*)malloc(size * sizeof(int));//создаем массив для хранения значений
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
        fprintf(stderr, "Ошибка открытия файла для записи: %s\n", filename);
        freeStack(stack);
        return;
    }

    printf("Введите числа (через пробел или запятую):\n");
    ssize_t bytesRead = getline(&buffer, &bufferSize, stdin);
    if (bytesRead == -1) {
        perror("Ошибка чтения ввода");
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
            printf("Некорректный ввод: %s\n", token);
        }
        token = strtok(NULL, " ,");
    }
    //запись в файл в правильном порядке
    writeStackToFile(stack, file);
    fclose(file);
    printf("Числа успешно записаны в файл %s.\n", filename);
    printf("Содержимое стека: ");
    //вывод
    printStack(stack->top);
    printf("\n");
    freeStack(stack);
    stack = createStack();
    free(buffer);
}

int loadSingleLineToStack(const char* filename, Stack* stack) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Ошибка открытия файла.\n");
        return -1;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    // Читаем только первую строку из файла
    if ((read = getline(&line, &len, file)) != -1) {
        char* token = strtok(line, ",");
        while (token != NULL) {
            while (isspace(*token)) token++; // Удаляем пробелы
            char* endptr;
            errno = 0;
            long num = strtol(token, &endptr, 10);

            if (errno == 0 && token != endptr && *endptr == '\0') {
                int data = (int)num;
                push(stack, data); // Добавляем данные в стек
            }
            else {
                printf("Не подошло: %s\n", token);
            }
            token = strtok(NULL, ",");
        }
    }

    free(line);
    fclose(file);
    return 0;
}






#endif
