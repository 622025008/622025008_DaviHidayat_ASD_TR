#ifndef GRAPH_H
#define GRAPH_H

#include "types.h"

typedef struct {
    int numVertices;
    char namaKota[MAX_KOTA][MAX_STR];
    int adjMatrix[MAX_KOTA][MAX_KOTA];
} Graph;

void initGraph(Graph *g, const char *filename);
void saveGraph(const Graph *g, const char *filename);
void displayGraph(const Graph *g);
void bfsGraph(const Graph *g, int startIdx);
void dfsGraph(const Graph *g, int startIdx);

#endif
