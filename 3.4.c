#include <stdio.h>
#include <locale.h>

#define MAX_IDENTIFIERS 36
#define MAX_LENGTH 12 + 1

int isValidChar(char c, int position) {
    return (c >= 'A' && c <= 'Z') || (c == '_') || (c >= '0' && c <= '9');
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

int extractIdentifiers(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH]) {
    int count = 0;
    int length = 0;
    char c;

    while ((c = getchar()) != '.' && count < MAX_IDENTIFIERS) {
        if (c == '\n') {
            continue; 
        }

        if (c == ' ') {
            if (length > 0) {
                identifiers[count][length] = '\0'; 

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
        }
    }


    if (length > 0) {
        identifiers[count][length] = '\0'; 

        if (isValidIdentifier(identifiers[count])) {
            count++;
        }
    }

    return count;
}

int isAllUpper(char identifier[]) {
    for (int i = 0; identifier[i] != '\0'; i++) {
        if (identifier[i] >= 'a' && identifier[i] <= 'z') {
            return 0; 
        }
    }
    return 1; 
}

void printUpperIDs(char identifiers[MAX_IDENTIFIERS][MAX_LENGTH], int count) {
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
    int count = extractIdentifiers(identifiers);
    printUpperIDs(identifiers, count); 

    return 0;
}
