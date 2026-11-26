#include <stdio.h>
#include <stdlib.h>
#include "stack_queue.h"

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

void enqueue(Queue *q, Paket p) {
    NodeSQ *node = (NodeSQ *)malloc(sizeof(NodeSQ));
    node->data = p;
    node->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = node;
    } else {
        q->rear->next = node;
        q->rear = node;
    }
}

int dequeue(Queue *q, Paket *out) {
    NodeSQ *temp;
    if (q->front == NULL) return 0;
    temp = q->front;
    *out = temp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return 1;
}

void displayQueue(const Queue *q) {
    NodeSQ *curr;
    int no = 1;
    if (!q->front) {
        printf("[!] Antrean pengiriman kosong.\n");
        return;
    }
    printf("\n=== ANTREAN PAKET SIAP KIRIM (QUEUE) ===\n");
    curr = q->front;
    while (curr) {
        printf("%d. [%s] ID:%d -> Tujuan: %s (%.2f kg)\n",
               no++, curr->data.resi, curr->data.id, curr->data.tujuan, curr->data.berat);
        curr = curr->next;
    }
}

void freeQueue(Queue *q) {
    Paket dummy;
    while (dequeue(q, &dummy));
}

void initStack(Stack *s) {
    s->top = NULL;
}

void push(Stack *s, Paket p) {
    NodeSQ *node = (NodeSQ *)malloc(sizeof(NodeSQ));
    node->data = p;
    node->next = s->top;
    s->top = node;
}

int pop(Stack *s, Paket *out) {
    NodeSQ *temp;
    if (s->top == NULL) return 0;
    temp = s->top;
    *out = temp->data;
    s->top = s->top->next;
    free(temp);
    return 1;
}

void displayStack(const Stack *s) {
    NodeSQ *curr;
    int no = 1;
    if (!s->top) {
        printf("[!] Riwayat pengiriman kosong.\n");
        return;
    }
    printf("\n=== RIWAYAT PENGIRIMAN TERAKHIR (STACK) ===\n");
    curr = s->top;
    while (curr) {
        printf("%d. [%s] ID:%d -> Tujuan: %s\n",
               no++, curr->data.resi, curr->data.id, curr->data.tujuan);
        curr = curr->next;
    }
}

void freeStack(Stack *s) {
    Paket dummy;
    while (pop(s, &dummy));
}
