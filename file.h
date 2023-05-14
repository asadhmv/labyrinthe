#ifndef BFS_H
#define BFS_H


//********************************************************************

//							QUEUE

//********************************************************************

struct queue {
  int items[800];
  int front;
  int rear;
};

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printQueue(struct queue* q);



#endif