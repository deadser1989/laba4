#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

int main(int argc, char* argv[]) {
    system("chcp 1251");
    system("cls");

    if (argc < 2) {
        printf("Использование: %s <имя файла>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    Stack* stack1 = createStack();
    Stack* stack2 = createStack();

    if (loadDataFromFileToStack(filename, stack1, stack2) == -1) {
        fprintf(stderr, "Ошибка загрузки данных из файла %s\n", filename);
        return 1;
    }

    printf("Предыдущий введённый ряд: ");
    printStack(stack1->top);
    printf("\n");

    printf("Предыдущий отсортированный ряд: ");
    printStack(stack2->top);
    printf("\n");

    freeStack(stack1);
    freeStack(stack2);
    return 0;
}
