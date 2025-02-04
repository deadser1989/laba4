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
        printf("�������������: %s <��� �����>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    Stack* stack1 = createStack();
    Stack* stack2 = createStack();

    // ��������� ������ �� ����� � ����
    if (loadDataFromFileToStack(filename, stack1, stack2) == -1) {
        fprintf(stderr, "������ �������� ������ �� ����� %s\n", filename);
        return 1;
    }

    printf("���������� �������� ���: ");
    printStack(stack1->top);
    printf("\n");

    printf("���������� ��������������� ���: ");
    printStack(stack2->top);
    printf("\n");

    // ���������� ����� � ������ � ����
    fillStackAndWriteToFile(filename);

    freeStack(stack1);
    stack1 = createStack();
    if (loadSingleLineToStack(filename, stack1) == -1) {
        fprintf(stderr, "������ �������� ������ �� ����� %s\n", filename);
        return 1;
    }
    insertionSortStack(stack1);
    printf("��������������� ���: ");
    printStack(stack1->top);
    printf("\n");
    writeStackToSecondLine(stack1, filename);

    // ����������� ������
    freeStack(stack1);
    freeStack(stack2);
    return 0;
}
