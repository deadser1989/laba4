#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h> 
#include "struct.h"
#include "sortvstavka.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");
    system("chcp 65001");
    system("cls");

    if (argc < 2) {
        printf("Использование: %s <имя файла>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    Stack* stack1 = createStack();
    Stack* stack2 = createStack();

    // Загружаем данные из файла в стек
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

    // Заполнение стека и запись в файл
    fillStackAndWriteToFile(filename);

    // Очистка stack1 перед загрузкой новых данных
    freeStack(stack1);
    stack1 = createStack();

    // Загружаем новые данные из файла в stack1
    if (loadSingleLineToStack(filename, stack1) == -1) {
        fprintf(stderr, "Ошибка загрузки данных из файла %s\n", filename);
        return 1;
    }

    // Сортируем стек
    insertionSortStack(stack1);

    // Вывод отсортированного ряда
    printf("Отсортированный ряд: ");
    printStack(stack1->top);
    printf("\n");

    // Освобождаем память
    freeStack(stack1);
    freeStack(stack2);
    return 0;
}
