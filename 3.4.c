#include <stdio.h>
#include <locale.h>

#define MAX_IDENTIFIERS 36
#define MAX_LENGTH 12 + 1

int isValidChar(char c, int position) {
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
        if (!isValidChar(identifier[i], i)) {
            return 0;
        }
    }

    return 1;
}

int findIDs(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH]) {
    int count = 0;
    int length = 0;
    char c;
    int better_lenght = 0;
    int maxCount = 0;

    while ((c = getchar()) != '.' && count < MAX_IDENTIFIERS) {
        if (c == '\n') {
            continue;
        }

        if (c == ' ') {
            if (length > 0) {
                identifiers[count][length] = '\0';

                if (isValidIdentifier(identifiers[count])) {
                    count++;
                    if (count == MAX_IDENTIFIERS) {
                        maxCount = 1;
                    }
                }
                length = 0;
            }
        }
        else {
            if (length < MAX_LENGTH - 1) {
                identifiers[count][length++] = c;
            }
            else if (!better_lenght) {
                printf("Идентификатор превышает максимальную длину %d символов\n", MAX_LENGTH - 1);
                better_lenght = 1;
            }
        }
    }

    if (length > 0) {
        identifiers[count][length] = '\0';
        if (isValidIdentifier(identifiers[count])) {
            count++;
            if (count == MAX_IDENTIFIERS) {
                maxCount = 1;
            }
        }
    }

    if (maxCount) {
        return -1; 
    }
    else {
        return count; 
    }
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
    int count = findIDs(identifiers);
    printUpperIDs(identifiers, count);

    return 0;
}
