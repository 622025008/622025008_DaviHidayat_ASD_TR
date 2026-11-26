#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paket.h"

void initPaketList(PaketList *list) {
    list->count = 0;
    list->capacity = 10;
    list->data = (Paket *)malloc(list->capacity * sizeof(Paket));
}

void addPaketToList(PaketList *list, Paket p) {
    if (list->count >= list->capacity) {
        list->capacity *= 2;
        list->data = (Paket *)realloc(list->data, list->capacity * sizeof(Paket));
    }
    list->data[list->count++] = p;
}

void loadPaket(PaketList *list, const char *filename) {
    FILE *fp = fopen(filename, "r");
    Paket p;
    if (!fp) return;

    while (fscanf(fp, "%d;%63[^;];%63[^;];%63[^;];%f;%63[^\n]\n",
                  &p.id, p.resi, p.pengirim, p.tujuan, &p.berat, p.status) == 6) {
        addPaketToList(list, p);
    }
    fclose(fp);
}

void savePaket(const PaketList *list, const char *filename) {
    FILE *fp = fopen(filename, "w");
    int i;
    if (!fp) return;
    for (i = 0; i < list->count; i++) {
        Paket p = list->data[i];
        fprintf(fp, "%d;%s;%s;%s;%.2f;%s\n",
                p.id, p.resi, p.pengirim, p.tujuan, p.berat, p.status);
    }
    fclose(fp);
}

void tampilkanPaket(const PaketList *list) {
    int i;
    if (list->count == 0) {
        printf("[!] Belum ada data paket.\n");
        return;
    }
    printf("\n%-5s | %-10s | %-15s | %-15s | %-8s | %-10s\n",
           "ID", "Resi", "Pengirim", "Tujuan", "Berat", "Status");
    printf("------------------------------------------------------------------------\n");
    for (i = 0; i < list->count; i++) {
        Paket p = list->data[i];
        printf("%-5d | %-10s | %-15s | %-15s | %-6.2fkg | %-10s\n",
               p.id, p.resi, p.pengirim, p.tujuan, p.berat, p.status);
    }
}

void bubbleSortBerat(PaketList *list, int ascending) {
    int i, j, cond;
    Paket temp;
    for (i = 0; i < list->count - 1; i++) {
        for (j = 0; j < list->count - i - 1; j++) {
            cond = ascending ? (list->data[j].berat > list->data[j + 1].berat)
                             : (list->data[j].berat < list->data[j + 1].berat);
            if (cond) {
                temp = list->data[j];
                list->data[j] = list->data[j + 1];
                list->data[j + 1] = temp;
            }
        }
    }
}

void selectionSortId(PaketList *list, int ascending) {
    int i, j, idx, cond;
    Paket temp;
    for (i = 0; i < list->count - 1; i++) {
        idx = i;
        for (j = i + 1; j < list->count; j++) {
            cond = ascending ? (list->data[j].id < list->data[idx].id)
                             : (list->data[j].id > list->data[idx].id);
            if (cond) idx = j;
        }
        if (idx != i) {
            temp = list->data[i];
            list->data[i] = list->data[idx];
            list->data[idx] = temp;
        }
    }
}

int sequentialSearchTujuan(const PaketList *list, const char *tujuan) {
    int found = 0, i;
    Paket p;
    for (i = 0; i < list->count; i++) {
        if (strcmp(list->data[i].tujuan, tujuan) == 0) {
            p = list->data[i];
            printf("  -> ID: %d | Resi: %s | Pengirim: %s | Berat: %.2f kg | Status: %s\n",
                   p.id, p.resi, p.pengirim, p.berat, p.status);
            found = 1;
        }
    }
    return found;
}

int binarySearchId(const PaketList *list, int targetId) {
    int left = 0, right = list->count - 1, mid;
    while (left <= right) {
        mid = left + (right - left) / 2;
        if (list->data[mid].id == targetId) return mid;
        if (list->data[mid].id < targetId) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void freePaketList(PaketList *list) {
    free(list->data);
    list->data = NULL;
    list->count = 0;
    list->capacity = 0;
}
