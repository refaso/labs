#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
static void appendToList(struct List** head_ref, int value);
static void printList(struct List* head);


// Структура списка
struct List {
    int data;
    struct List* Next;
};

// Функция для создания нового списка
static struct List* createList(int value) {
    struct List* new_list = (struct List*)malloc(sizeof(struct List));
    if (new_list == NULL) {
        printf("Ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    new_list->data = value;
    new_list->Next = NULL;
    return new_list;
}

// Функция для извлечения отрицательных элементов и их сортировки
static struct List* extractAndSortNegatives(struct List** head_ref) {
    struct List* neg_head = NULL;
    struct List* current = *head_ref;
    struct List* prev = NULL;

    while (current != NULL) {
        if (current->data < 0) {
            if (prev == NULL) {
                *head_ref = current->Next;
            }
            else {
                prev->Next = current->Next;
            }

            current->Next = neg_head;
            neg_head = current;

            current = prev != NULL ? prev->Next : *head_ref;
        }
        else {
            prev = current;
            current = current->Next;
        }
    }

    struct List* sorted_neg = NULL;
    while (neg_head != NULL) {
        struct List* next_list = neg_head->Next;
        struct List** insert_pos = &sorted_neg;

        while (*insert_pos != NULL && (*insert_pos)->data < neg_head->data) {
            insert_pos = &((*insert_pos)->Next);
        }

        neg_head->Next = *insert_pos;
        *insert_pos = neg_head;

        neg_head = next_list;
    }

    return sorted_neg;
}

int main() {
    setlocale(0, "");
    // Ввод элементов списка
    struct List* list_head = NULL;
    int num_elements;
    printf("Введите количество элементов списка: ");
    scanf_s("%d", &num_elements);

    for (int i = 0; i < num_elements; ++i) {
        int value;
        printf("Введите %d-й элемент: ", i + 1);
        scanf_s("%d", &value);
        appendToList(&list_head, value);
    }

    // Печать исходного списка
    printf("Исходный список:\n");
    printList(list_head);

    // Извлечение и сортировка отрицательных элементов
    struct List* negative_sorted_list = extractAndSortNegatives(&list_head);

    // Печать результата
    printf("Отрицательные элементы, отсортированные по возрастанию:\n");
    printList(negative_sorted_list);

    // Освобождение памяти
    struct List* temp;
    while (list_head != NULL) {
        temp = list_head;
        list_head = list_head->Next;
        free(temp);
    }

    while (negative_sorted_list != NULL) {
        temp = negative_sorted_list;
        negative_sorted_list = negative_sorted_list->Next;
        free(temp);
    }

    return 0;
}

// Функция для добавления элемента в конец списка
static void appendToList(struct List** head_ref, int value) {
    struct List* new_list = createList(value);
    struct List* last = *head_ref;

    if (*head_ref == NULL) {
        *head_ref = new_list;
        return;
    }

    while (last->Next != NULL)
        last = last->Next;

    last->Next = new_list;
}

// Функция для печати списка
static void printList(struct List* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->Next;
    }
    printf("\n");
}
