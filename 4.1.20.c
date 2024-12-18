#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Прототипы функций
static void appendToList(struct List** head_ref, int value);
static void printList(struct List* head);

// Структура списка
struct List {
    int data; // Хранит данные
    struct List* Next; // Указатель на следующий элемент
};

// Функция для создания нового элемента списка
static struct List* createList(int value) {
    struct List* new_list = (struct List*)malloc(sizeof(struct List));
    if (new_list == NULL) {
        printf("Ошибка выделения памяти\n");
        return NULL;
    }
    new_list->data = value;
    new_list->Next = NULL;
    return new_list;
}

// Функция для извлечения отрицательных элементов и их сортировки
static struct List* extractAndSortNegatives(struct List** head_ref) {
    struct List* neg_head = NULL; // Глава нового списка с отрицательными элементами
    struct List* current = *head_ref; // Текущий элемент исходного списка
    struct List* prev = NULL; // Предыдущий элемент

    while (current != NULL) {
        if (current->data < 0) { // Обработка отрицательных элементов
            if (prev == NULL) {
                *head_ref = current->Next; // Обновляем голову исходного списка
            }
            else {
                prev->Next = current->Next; // Связываем предыдущий элемент с следующим
            }

            current->Next = neg_head; // Добавляем текущий элемент в начало нового списка
            neg_head = current; // Обновляем голову нового списка
            current = prev != NULL ? prev->Next : *head_ref; // Переход к следующему элементу
        }
        else {
            prev = current; // Сохраняем ссылку на текущий элемент
            current = current->Next; // Переходим к следующему элементу
        }
    }

    struct List* sorted_neg = NULL; // Голова отсортированного списка
    while (neg_head != NULL) {
        struct List* next_list = neg_head->Next; // Сохраняем следующий элемент
        struct List** insert_pos = &sorted_neg; // Начальная позиция для вставки

        while (*insert_pos != NULL && (*insert_pos)->data < neg_head->data) {
            insert_pos = &((*insert_pos)->Next); // Ищем подходящее место для вставки
        }

        neg_head->Next = *insert_pos; // Вставляем элемент на правильную позицию
        *insert_pos = neg_head; // Обновляем указатель на вставленный элемент
        neg_head = next_list; // Переходим к следующему отрицательному элементу
    }

    return sorted_neg; // Возвращаем отсортированный список
}

int main() {
    struct List* list_head = NULL; // Голова исходного списка
    int value; // Хранит введенное значение
    int count_minus = 0, count_plus =  0; 
    setlocale(0, "");

    printf("Введите элементы списка (типа int) \nДля завершения введите любой символ (.):\n");


    while (1) {
        int value;
        printf("Введите элемент: ");

        // Считываем целое число
        if (scanf_s("%d", &value) == 1) {
            if (value < 0) {
                count_minus++;
            }
            if (value > 0) {
                count_plus++;
            }
            appendToList(&list_head, value); // Если введено число, добавляем его в список
        }
        else {
            scanf_s("%*s"); // Очистка некорректного ввода
            break; // Завершение ввода при вводе не чисел
        }
    }

    printf("Исходный список:\n");
    printList(list_head); // Печать исходного списка

    struct List* negative_sorted_list = extractAndSortNegatives(&list_head); // Получаем отсортированный список отрицательных элементов
    if (count_minus == 0) {
        printf("Нет отрицательных элементов\n");
    }
    else {
        printf("Отрицательные элементы, отсортированные по возрастанию:\n");
    }
    printList(negative_sorted_list); // Печать отсортированных отрицательных элементов
    if (count_plus == 0) {
        printf("Нет положительных элементов");
    }
    else {
        printf("Измененный исходный список (без отрицательных элементов):\n");
    }
    printList(list_head); // Печать измененного списка

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
        *head_ref = new_list; // Новый элемент становится головой списка
        return;
    }

    while (last->Next != NULL) // Идем до конца списка
        last = last->Next;

    last->Next = new_list; // Добавляем новый элемент в конец списка
}

// Функция для печати списка
static void printList(struct List* head) {
    while (head != NULL) {
        printf("%d ", head->data); // Выводим значение текущего элемента
        head = head->Next; // Переходим к следующему элементу
    }
    printf("\n");
}
