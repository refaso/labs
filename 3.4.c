#include <stdio.h>
#include <locale.h>

#define MAX_IDENTIFIERS 4
#define MAX_LENGTH 4

int isValidChar(char c) {
    return (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z');
}

int isValidIdentifier(char identifier[]) {
    if (identifier[0] == '\0') {
        return 0;
    }

    if (identifier[0] >= '0' && identifier[0] <= '9') {
        return 0;
    }

    for (int i = 0; identifier[i] != '\0'; i++) {
        if (!isValidChar(identifier[i])) {
            return 0;
        }
    }
    return 1;
}

int findIDs(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH], int* exceedsLength) {
    int count = 0;
    int length = 0;
    char c;

    *exceedsLength = 0;

    while ((c = getchar()) != '.' && count < MAX_IDENTIFIERS) {
        if (c == '\n' || c == '\r') {
            continue;
        }

        if (c == ' ') {
            if (length > 0) {
                identifiers[count][length] = '\0';

                if (length >= MAX_LENGTH - 1 && *exceedsLength == 0) {
                    printf("Идентификатор(ы) превышает максимальную длину %d символов\n", MAX_LENGTH - 1);
                    *exceedsLength = 1;
                }

                if (isValidIdentifier(identifiers[count])) {
                    count++;
                }

                length = 0;
            }
        }
        else {
            if (length < MAX_LENGTH - 1) {
                identifiers[count][length++] = c;
            }
            else if (*exceedsLength == 0) {
                printf("Идентификатор(ы) превышает максимальную длину %d символов\n", MAX_LENGTH - 1);
                *exceedsLength = 1;
            }
        }
    }

    if (c != '.' && count >= MAX_IDENTIFIERS) {
        printf("Превышено максимальное количество идентификаторов: %d\n", MAX_IDENTIFIERS);
        return -1;
    }

    if (length > 0) {
        identifiers[count][length] = '\0';
        if (length >= MAX_LENGTH - 1 && *exceedsLength == 0) {
            printf("Идентификатор(ы) превышает максимальную длину %d символов\n", MAX_LENGTH - 1);
            *exceedsLength = 1;
        }

        if (isValidIdentifier(identifiers[count])) {
            count++;
        }
    }

    return count;
}

int isAllUpper(char identifier[]) {
    int hasUpper = 0;
    for (int i = 0; identifier[i] != '\0'; i++) {
        if (identifier[i] >= 'A' && identifier[i] <= 'Z') {
            hasUpper = 1;
        }
        else if (identifier[i] >= 'a' && identifier[i] <= 'z') {
            return 0;
        }
    }
    return hasUpper;
}

void printUpperIDs(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH], int count) {
    if (count < 0) {
        return;
    }

    int hasUpperID = 0;
    for (int i = 0; i < count; i++) {
        if (isAllUpper(identifiers[i])) {
            printf("%s\n", identifiers[i]);
            hasUpperID = 1;
        }
    }

    if (!hasUpperID) {
        printf("Нет идентификаторов с заглавными буквами\n");
    }
}

int main() {
    char identifiers[MAX_IDENTIFIERS][MAX_LENGTH];
    setlocale(0, "");

    printf("Введите последовательность идентификаторов, оканчивающуюся точкой:\n");
    int exceedsLength;
    int count = findIDs(identifiers, &exceedsLength);

    if (exceedsLength || count < 0) {
        return 0;
    }

    printUpperIDs(identifiers, count);

    return 0;
}
