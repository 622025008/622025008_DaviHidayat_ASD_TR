#ifndef STACK_QUEUE_H
#define STACK_QUEUE_H

#include "types.h"

typedef struct NodeSQ {
    Paket data;
    struct NodeSQ *next;
} NodeSQ;

typedef struct {
    NodeSQ *front;
    NodeSQ *rear;
} Queue;

typedef struct {
    NodeSQ *top;
} Stack;

void initQueue(Queue *q);
void enqueue(Queue *q, Paket p);
int dequeue(Queue *q, Paket *out);
void displayQueue(const Queue *q);
void freeQueue(Queue *q);

void initStack(Stack *s);
void push(Stack *s, Paket p);
int pop(Stack *s, Paket *out);
void displayStack(const Stack *s);
void freeStack(Stack *s);

#endif
