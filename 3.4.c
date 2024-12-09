#include <stdio.h>
#include <locale.h>

#define MAX_IDENTIFIERS 36
#define MAX_LENGTH 12+1  

static void extractID(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH], int* count) {
    char c;
    int j = 0;

    while ((c = getchar()) != '.' && *count < MAX_IDENTIFIERS) {
        if (c == '\n') {
            continue;
        }
        if (c == ' ') {
            if (j > 0) {
                identifiers[*count][j] = '\0';
                (*count)++;
                j = 0;
            }
        }
        else {
            if (j < MAX_LENGTH - 1) {
                identifiers[*count][j++] = c;
            }
        }
    }
    if (j > 0) {
        identifiers[*count][j] = '\0';
        (*count)++;
    }
}

static void printUpperID(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH], int count) {
    int hasUpperID = 0;
    for (int i = 0; i < count; i++) {
        int isUpper = 1;
        for (int k = 0; identifiers[i][k] != '\0'; k++) {
            if (identifiers[i][k] < 'A' || identifiers[i][k] > 'Z') {
                isUpper = 0;
                break;
            }
        }
        if (isUpper) {
            printf("%s\n", identifiers[i]);
            hasUpperID = 1;
        }
    }
    if (!hasUpperID) {
        printf("нет слов в верхнем регистре\n"); 
    }
}

int main() {
    int count = 0;
    char identifiers[MAX_IDENTIFIERS][MAX_LENGTH];
    setlocale(0, "");

    printf("Введите последовательность идентификаторов, оканчивающуюся точкой:\n");
    extractID(identifiers, &count);
    printUpperID(identifiers, count);

    return 0;
}
