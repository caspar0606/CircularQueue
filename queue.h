#ifndef __QUEUE__
#define __QUEUE__

typedef struct {
	int n;
	int cap;
	int front;
	int rear;
	void **array;
} Queue;

Queue* makeQ();
void enQ(Queue *Q, void* data);
void* deQ(Queue *Q);
void emptyQ(Queue *Q);
void growQ(Queue *Q);


#endif