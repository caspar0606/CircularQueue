#include <stdlib.h>
#include <stdio.h>

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
		perror("enQ: Null Queue/gates Pointer");
		exit(EXIT_FAILURE);
	}

	if (Q->n == Q->cap) {
		growQ(Q);
	}

	Q->rear = (Q->rear + 1) % Q->n;
	Q->array[Q->rear] = gate;
	Q->n++;

	return;
}

void* deQ(Queue *Q) {
	if (!Q || (Q->n < 1)) {
		perror("deQ: Null/Empty Queue");
		exit(EXIT_FAILURE);
	}
	void* ptr = Q->array[Q->front];
	Q->front = (Q->front + 1) % Q->n;
	return ptr;
}

void emptyQ(Queue *Q) {
	if (!Q) {
		perror("emptyQ: Null Queue Pointer");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < Q->n; i++) {
		if (Q->array[i]) {
			free(Q->array[i]);
		}
	}
	return;
}

void growQ(Queue *Q) {
	if (!Q) {
		perror("growQ: Null Queue Pointer");
		exit(EXIT_FAILURE);
	}

	void **tmp = xrealloc(Q->array, sizeof(void*)*Q->cap*2);
	if (!tmp) {
		perror("growQ: realloc failed");
		exit(EXIT_FAILURE);
	}
	Q->cap *= 2;

	for (int i = 0; i < Q->n; i++) {
		if (Q->array[i]) {
			tmp[i] = Q->array[(Q->front + i) % Q->cap];
		}
	}
	free(Q->array);
	Q->array = tmp;
	Q->front = 0;
	Q->rear = Q->n;
	return;
}

