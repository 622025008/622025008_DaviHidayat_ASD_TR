#include <stdio.h>
#include <string.h>
#include "utils.h"

void clearBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int inputInt(const char *prompt) {
    int val;
    char extra;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &val, &extra) == 2 && extra == '\n') {
            return val;
        }
        printf("[!] Input tidak valid. Masukkan angka bulat!\n");
        if (extra != '\n') clearBuffer();
    }
}

float inputFloat(const char *prompt) {
    float val;
    char extra;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f%c", &val, &extra) == 2 && extra == '\n') {
            return val;
        }
        printf("[!] Input tidak valid. Masukkan angka!\n");
        if (extra != '\n') clearBuffer();
    }
}

void inputString(const char *prompt, char *dest, int maxLen) {
    int len;
    while (1) {
        printf("%s", prompt);
        if (fgets(dest, maxLen, stdin) != NULL) {
            len = (int)strlen(dest);
            if (len > 0 && dest[len - 1] == '\n') {
                dest[len - 1] = '\0';
                len--;
            } else {
                clearBuffer();
            }
            if (len > 0) {
                return;
            }
        }
        printf("[!] Input tidak boleh kosong!\n");
    }
}
