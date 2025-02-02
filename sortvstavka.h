
#ifndef SORTVSTAVKA_H
#define SORTVSTAVKA_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <time.h>

void insertion_sort(stack* s) { 
    if (s->topindex < 1) { //снова если пуст то ужде отсортирован
        return;
    }
    stack temp;
    init_stack(&temp);

    //из орига в временный + сортируем
    while (s->topindex >= 0) {
        // верхний элемент извлекаем
        int current = s->data[s->topindex];
        s->topindex--;
        // если элемент больше текущего перемещаем его обратно в ориг
        while (temp.topindex >= 0 && temp.data[temp.topindex] > current) {
            s->data[++s->topindex] = temp.data[temp.topindex];
            temp.topindex--;
        }
       //текующий элем во временный стек
        temp.data[++temp.topindex] = current;
    }
    // перемещаем отсортированные элементы обратно в оригинальный стек
    while (temp.topindex >= 0) {
        s->data[++s->topindex] = temp.data[temp.topindex];
        temp.topindex--;
    }
    free_stack(&temp);
}
#endif 