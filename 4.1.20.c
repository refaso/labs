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
    setlocale(0, "");
    struct List* list_head = NULL; // Голова исходного списка
    char input[20]; // Буфер для ввода строки
    int value; // Хранит введенное значение

    printf("Введите элементы списка (для завершения введите '.'): \n");

    while (1) {
        printf("Введите элемент: ");
        scanf_s("%s", input, (unsigned)_countof(input)); // Чтение строки с указанием размера буфера

        if (strcmp(input, ".") == 0) {
            break; // Завершение ввода при введении точки
        }

        if (sscanf_s(input, "%d", &value) != 1) { // Преобразуем строку в число
            printf("Некорректный ввод! Введите целое число или '.' для завершения.\n");
            continue; // Запрашиваем ввод повторно
        }

        appendToList(&list_head, value); // Добавляем элемент в список
    }

    printf("Исходный список:\n");
    printList(list_head); // Печать исходного списка

    struct List* negative_sorted_list = extractAndSortNegatives(&list_head); // Получаем отсортированный список отрицательных элементов

    printf("Отрицательные элементы, отсортированные по возрастанию:\n");
    printList(negative_sorted_list); // Печать отсортированных отрицательных элементов

    printf("Измененный исходный список (без отрицательных элементов):\n");
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

    return 0; // Завершение программы
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
