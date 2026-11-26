#ifndef PAKET_H
#define PAKET_H

#include "types.h"

typedef struct {
    Paket *data;
    int count;
    int capacity;
} PaketList;

void initPaketList(PaketList *list);
void addPaketToList(PaketList *list, Paket p);
void loadPaket(PaketList *list, const char *filename);
void savePaket(const PaketList *list, const char *filename);
void tampilkanPaket(const PaketList *list);
void bubbleSortBerat(PaketList *list, int ascending);
void selectionSortId(PaketList *list, int ascending);
int sequentialSearchTujuan(const PaketList *list, const char *tujuan);
int binarySearchId(const PaketList *list, int targetId);
void freePaketList(PaketList *list);

#endif
