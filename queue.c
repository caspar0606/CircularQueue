#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "queue.h"

Queue* makeQ() {
	Queue *Q = malloc(sizeof(Queue));
	Q->n = 0;
	Q->front = 0;
	Q->rear = 0;
	Q->cap = 1;
	Q->array = malloc(sizeof(void*));
	return Q;
}

void enQ(Queue *Q, void *gate) {
	if (!Q || !gate) {
		fprintf(stderr, "growQ: null Queue/Gate*\n");
		exit(EXIT_FAILURE);
	}

	if (Q->n == Q->cap) {
		growQ(Q);
	}

	Q->array[Q->rear] = gate;
	Q->rear = (Q->rear + 1) % Q->cap;
	Q->n++;

	return;
}

void* deQ(Queue *Q) {
	if (!Q || (Q->n < 1)) {
		fprintf(stderr, "growQ: null/empty Queue*\n");
		exit(EXIT_FAILURE);
	}
	void* ptr = Q->array[Q->front];
	Q->front = (Q->front + 1) % Q->cap;
    Q->n--;
	return ptr;
}

void emptyQ(Queue *Q) {
	if (!Q) {
		fprintf(stderr, "growQ: null Queue*\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < Q->n; i++) {
        free(Q->array[i]);
	}
	return;
}

void growQ(Queue *Q) {
	if (!Q) {
		fprintf(stderr, "growQ: null Queue*\n");
		exit(EXIT_FAILURE);
	}

    int new_cap = Q->cap * 2;
	void **new = malloc(sizeof(void*) * new_cap);

	if (!new) {
		perror("growQ: malloc failed");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < Q->n; i++) {
        new[i] = Q->array[(Q->front + i) % Q->cap];
	}

    free(Q->array);
    Q->cap = new_cap;
	Q->array = new;
	Q->front = 0;
	Q->rear = Q->n;
	return;
}

