#include <stdio.h>
#include <string.h>
#include "graph.h"

void saveGraph(const Graph *g, const char *filename) {
    FILE *fp = fopen(filename, "w");
    int i, j;
    if (!fp) return;
    fprintf(fp, "%d\n", g->numVertices);
    for (i = 0; i < g->numVertices; i++) {
        fprintf(fp, "%s\n", g->namaKota[i]);
    }
    for (i = 0; i < g->numVertices; i++) {
        for (j = 0; j < g->numVertices; j++) {
            fprintf(fp, "%d%s", g->adjMatrix[i][j], (j == g->numVertices - 1) ? "" : " ");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void initGraph(Graph *g, const char *filename) {
    FILE *fp = fopen(filename, "r");
    int i, j;
    int defaultAdj[5][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };

    if (fp) {
        fscanf(fp, "%d\n", &g->numVertices);
        for (i = 0; i < g->numVertices; i++) {
            fscanf(fp, "%63[^\n]\n", g->namaKota[i]);
        }
        for (i = 0; i < g->numVertices; i++) {
            for (j = 0; j < g->numVertices; j++) {
                fscanf(fp, "%d", &g->adjMatrix[i][j]);
            }
        }
        fclose(fp);
        return;
    }

    g->numVertices = 5;
    strcpy(g->namaKota[0], "Jakarta");
    strcpy(g->namaKota[1], "Bandung");
    strcpy(g->namaKota[2], "Semarang");
    strcpy(g->namaKota[3], "Yogyakarta");
    strcpy(g->namaKota[4], "Surabaya");

    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            g->adjMatrix[i][j] = defaultAdj[i][j];

    saveGraph(g, filename);
}

void displayGraph(const Graph *g) {
    int i, j;
    printf("\n=== PETA GUDANG & RUTE PENGIRIMAN ===\n");
    for (i = 0; i < g->numVertices; i++) {
        printf("[%d] %-12s -> Terhubung ke: ", i, g->namaKota[i]);
        for (j = 0; j < g->numVertices; j++) {
            if (g->adjMatrix[i][j]) printf("%s ", g->namaKota[j]);
        }
        printf("\n");
    }
}

void bfsGraph(const Graph *g, int startIdx) {
    int visited[MAX_KOTA] = {0};
    int queue[MAX_KOTA], front = 0, rear = 0;
    int curr, i;

    visited[startIdx] = 1;
    queue[rear++] = startIdx;

    printf("Hasil BFS (Rute Melebar dari %s): ", g->namaKota[startIdx]);
    while (front < rear) {
        curr = queue[front++];
        printf("%s", g->namaKota[curr]);
        for (i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[curr][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
        if (front < rear) printf(" -> ");
    }
    printf("\n");
}

static void dfsUtil(const Graph *g, int curr, int visited[], int *first) {
    int i;
    visited[curr] = 1;
    if (!(*first)) printf(" -> ");
    printf("%s", g->namaKota[curr]);
    *first = 0;

    for (i = 0; i < g->numVertices; i++) {
        if (g->adjMatrix[curr][i] && !visited[i]) {
            dfsUtil(g, i, visited, first);
        }
    }
}

void dfsGraph(const Graph *g, int startIdx) {
    int visited[MAX_KOTA] = {0};
    int first = 1;
    printf("Hasil DFS (Penelusuran Mendalam dari %s): ", g->namaKota[startIdx]);
    dfsUtil(g, startIdx, visited, &first);
    printf("\n");
}
