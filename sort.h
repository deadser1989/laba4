#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <limits.h>

// ������� ��� �����
void merge_stacks(stack* left, stack* right, stack* result) {
    stack temp;
    init_stack(&temp);

    while (!is_empty(left) && !is_empty(right)) {
        if (left->data[left->topindex] < right->data[right->topindex]) {
            push(&temp, pop(left));
        }
        else {
            push(&temp, pop(right));
        }
    }
    while (!is_empty(left)) {
        push(&temp, pop(left));
    }

    while (!is_empty(right)) {
        push(&temp, pop(right));
    }

    while (!is_empty(&temp)) {
        push(result, pop(&temp)); // ����� ��������� �� ���������
    }
    free_stack(&temp);
}

// ���������
void merge_sort(stack* s) {
    if (is_empty(s) || s->topindex == 0) { // ���� ���� �� �� ����������� ���
        return; 
    }
    stack left, right;
    init_stack(&left);
    init_stack(&right);

    int mid = (s->topindex + 1) / 2; // ��������
    for (int i = 0; i < mid; i++) {
        push(&left, pop(s)); // ������ ���������  � ���� ������ � ����
    }
    while (!is_empty(s)) {
        push(&right, pop(s));
    }

    merge_sort(&left);//��������� ��������
    merge_sort(&right);

    merge_stacks(&left, &right, s);

    free_stack(&left);
    free_stack(&right);
}