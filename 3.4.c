#include <stdio.h>
#include <locale.h>

#define MAX_IDENTIFIERS 36
#define MAX_LENGTH 13  // 12 символов 

static void extractID(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH], int* count) {
    char c;
    int j = 0;

    while ((c = getchar()) != '.' && *count < MAX_IDENTIFIERS) {
        if (c == '\n') {
            continue; // Игнорируем перенос строки
        }
        if (c == ' ') {
            if (j > 0) {
                identifiers[*count][j] = '\0';  // Завершение идентификатора
                (*count)++;
                j = 0; // Сброс длины идентификатора
            }
        }
        else {
            if (j < MAX_LENGTH - 1) {  // Проверка длины идентификатора
                identifiers[*count][j++] = c;
            }
        }
    }
    if (j > 0) {  // Добавляем последний идентификатор, если есть
        identifiers[*count][j] = '\0';
        (*count)++;
    }
}

static void printUpperID(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH], int count) {
    for (int i = 0; i < count; i++) {
        int isUpper = 1;  // Предполагаем, что идентификатор состоит из заглавных букв
        for (int k = 0; identifiers[i][k] != '\0'; k++) {
            if (identifiers[i][k] < 'A' || identifiers[i][k] > 'Z') {
                isUpper = 0;
                break;
            }
        }
        if (isUpper) {
            printf("%s\n", identifiers[i]);
        }
    }
}

int main() {
    int count = 0;
    char identifiers[MAX_IDENTIFIERS][MAX_LENGTH]; // Объявляем массив для идентификаторов
    setlocale(0, "");

    printf("Введите последовательность идентификаторов, оканчивающуюся точкой:\n");
    extractID(identifiers, &count); // Передаем массив в функцию
    printUpperID(identifiers, count); // Выводим заглавные идентификаторы

    return 0;
}
