#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Прототипы функций
static void appendToList(struct List** head_ref, int value);
static void printList(struct List* head);

// Структура списка
struct List {
    int data;      // Поле для хранения данных
    struct List* Next;  // Указатель на следующий элемент списка
};

// Функция для создания нового списка
static struct List* createList(int value) {
    struct List* new_list = (struct List*)malloc(sizeof(struct List)); // Выделяем память под новый элемент списка
    if (new_list == NULL) {  
        printf("Ошибка выделения памяти\n");  // Сообщение об ошибке если память не была успешно выделена
        return 0; // Завершаем выполнение программы
    }
    new_list->data = value;  // Заполняем значение данных
    new_list->Next = NULL;   // Устанавливаем указатель на следующий элемент в NULL
    return new_list;         // Возвращаем созданный элемент списка
}

// Функция для извлечения отрицательных элементов и их сортировки
static struct List* extractAndSortNegatives(struct List** head_ref) {
    struct List* neg_head = NULL;  // Указатель на голову нового списка с отрицательными элементами
    struct List* current = *head_ref;  // Указатель на текущий элемент исходного списка
    struct List* prev = NULL;  // Указатель на предыдущий элемент

    while (current != NULL) {  // Пока не достигли конца списка
        if (current->data < 0) {  // Если текущий элемент отрицателен
            if (prev == NULL) {  // Если это первый элемент списка
                *head_ref = current->Next;  // Обновляем голову исходного списка
            } else {  // Если это не первый элемент
                prev->Next = current->Next;  // Связываем предыдущий элемент с следующим за текущим
            }

            current->Next = neg_head;  // Добавляем текущий элемент в начало нового списка
            neg_head = current;  // Обновляем голову нового списка

            current = prev != NULL ? prev->Next : *head_ref;  // Переходим к следующему элементу
        } else {  // Если текущий элемент не отрицателен
            prev = current;  // Сохраняем ссылку на предыдущий элемент
            current = current->Next;  // Переходим к следующему элементу
        }
    }

    struct List* sorted_neg = NULL;  // Указатель на голову отсортированного списка
    while (neg_head != NULL) {  // Пока не обработаны все отрицательные элементы
        struct List* next_list = neg_head->Next;  // Сохраняем ссылку на следующий элемент
        struct List** insert_pos = &sorted_neg;  // Начальная позиция для вставки

        while (*insert_pos != NULL && (*insert_pos)->data < neg_head->data) {  // Ищем подходящее место для вставки
            insert_pos = &((*insert_pos)->Next);  // Двигаемся дальше по списку
        }

        neg_head->Next = *insert_pos;  // Вставляем элемент на правильную позицию
        *insert_pos = neg_head;  // Обновляем указатель на вставленный элемент

        neg_head = next_list;  // Переходим к следующему отрицательному элементу
    }

    return sorted_neg;  // Возвращаем отсортированный список отрицательных элементов
}

int main() {
    setlocale(0, "");  
    int num_elements;  // Количество элементов в списке
    struct List* temp;  // Временная переменная для освобождения памяти
    int value;  // Переменная для хранения введенного значения

    // Ввод элементов списка
    struct List* list_head = NULL;  // Голова исходного списка
    
    printf("Введите количество элементов списка: ");  // Запрашиваем количество элементов
    if (scanf_s("%d", &num_elements) != 1 || num_elements <= 0) {  // Проверка корректности ввода
        printf("Некорректный ввод! Количество элементов должно быть положительным целым числом\n");  // Сообщение об ошибке
        return 0;  // Завершаем выполнение программы
    }

    for (int i = 0; i < num_elements; ++i) {  // Цикл для ввода значений
        printf("Введите %d-й элемент: ", i + 1);  // Запрашиваем очередной элемент
        if (scanf_s("%d", &value) != 1) {  // Проверка корректности ввода
            printf("Некорректный ввод! Элемент должен быть целым числом!\n");  // Сообщение об ошибке
            return 0;  // Завершаем выполнение программы
        }
        appendToList(&list_head, value);  // Добавляем элемент в список
    }

    // Печать исходного списка
    printf("Исходный список:\n");
    printList(list_head);  // Вызываем функциюю для печати списка

    // Извлечение и сортировка отрицательных элементов
    struct List* negative_sorted_list = extractAndSortNegatives(&list_head);  // Получаем отсортированный список отрицательных элементов

    // Печать результата
    printf("Отрицательные элементы, отсортированные по возрастанию:\n");
    printList(negative_sorted_list);  // Печать отсортированных отрицательных элементов

    // Освобождение памяти
    
    while (list_head != NULL) {  // Освобождаем память исходного списка
        temp = list_head;
        list_head = list_head->Next;
        free(temp);
    }

    while (negative_sorted_list != NULL) {  // Освобождаем память отсортированного списка
        temp = negative_sorted_list;
        negative_sorted_list = negative_sorted_list->Next;
        free(temp);
    }

    return 0;  // Завершение программы
}

// Функция для добавления элемента в конец списка
static void appendToList(struct List** head_ref, int value) {
    struct List* new_list = createList(value);  // Создаём новый элемент списка
    struct List* last = *head_ref;  // Указатель на последний элемент списка

    if (*head_ref == NULL) {  // Если список пустой
        *head_ref = new_list;  // Новый элемент становится головой списка
        return;  // Выход из функции
    }

    while (last->Next != NULL)  // Идем до конца списка
        last = last->Next;  // Переходим к следующему элементу

    last->Next = new_list;  // Добавляем новый элемент в конец списка
}

// Функция для печати списка
static void printList(struct List* head) {
    while (head != NULL) {  // Пока не достигнут конец списка
        printf("%d ", head->data);  // Выводим значение текущего элемента
        head = head->Next;  // Переходим к следующему элементу
    }
    printf("\n");  // Перевод строки после завершения печати
}
