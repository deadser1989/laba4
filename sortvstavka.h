
#ifndef SORTVSTAVKA_H
#define SORTVSTAVKA_H
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <time.h>

void insertion_sort(stack* s) { 
    if (s->topindex < 1) { //����� ���� ���� �� ���� ������������
        return;
    }
    stack temp;
    init_stack(&temp);

    //�� ����� � ��������� + ���������
    while (s->topindex >= 0) {
        // ������� ������� ���������
        int current = s->data[s->topindex];
        s->topindex--;
        // ���� ������� ������ �������� ���������� ��� ������� � ����
        while (temp.topindex >= 0 && temp.data[temp.topindex] > current) {
            s->data[++s->topindex] = temp.data[temp.topindex];
            temp.topindex--;
        }
       //�������� ���� �� ��������� ����
        temp.data[++temp.topindex] = current;
    }
    // ���������� ��������������� �������� ������� � ������������ ����
    while (temp.topindex >= 0) {
        s->data[++s->topindex] = temp.data[temp.topindex];
        temp.topindex--;
    }
    free_stack(&temp);
}
#endif 