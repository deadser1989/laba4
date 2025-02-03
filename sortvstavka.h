#ifndef SORTVSTAVKA_H
#define SORTVSTAVKA_H

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"


void insertionSortStack(Stack* stack) {
    Stack* sortedStack = createStack();
    while (!isEmpty(stack)) {
        int temp = pop(stack);

        while (!isEmpty(sortedStack) && sortedStack->top->data < temp) {
            push(stack, pop(sortedStack));
        }

        push(sortedStack, temp);
    }

    // Переносим отсортированные элементы обратно в исходный стек
    while (!isEmpty(sortedStack)) {
        push(stack, pop(sortedStack));
    }

    freeStack(sortedStack);
}

void printSortedStack(Stack* stack) {
    printf("Отсортированные данные: ");
    printStack(stack->top);
    printf(", ");
}


void writeInputToFile(const char* filename, Stack* stack) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Ошибка открытия файла для записи: %s\n", filename);
        return;
    }

    node* current = stack->top;
    while (current != NULL) {
        fprintf(file, "%d", current->data);
        current = current->next;
        if (current != NULL) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, ", ");
    fprintf(file, "\n");
    fclose(file);
}

#endif
