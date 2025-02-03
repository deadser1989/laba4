#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

    // Запись в файл в правильном порядке
    writeSortedStackToFile(filename, stack);
    fclose(file);
    printf("Числа успешно записаны в файл %s.\n", filename);
    printf("Содержимое стека: ");
    printStack(stack->top);
    freeStack(stack);
    free(buffer);
}
