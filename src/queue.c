#include "emerald.h"

queue* q_create () {
  queue *q;
  q = (queue *)malloc(sizeof(queue));
  q->elements = (em_token *)malloc(sizeof(em_token) * q_MAXELEMENTS);
  q->size = 0;
  q->capacity = q_MAXELEMENTS;
  q->front = 0;
  q->rear = -1;
  return q;
}

em_token q_dequeue (queue *q) {
  if (q->size == 0) {
    die("em_token queue is empty\n");
  }

  em_token element = q->elements[q->front];

  q->size--;
  q->front++;

  if (q->front == q->capacity) {
    q->front = 0;
  }

  return element;
}

void q_enqueue (queue *q, em_token element) {
  if (q->size == q->capacity) {
    die("em_token queue is full\n");
  }

  q->size++;
  q->rear++;

  if (q->rear == q->capacity) {
    q->rear = 0;
  }

  q->elements[q->rear] = element;
}

void q_dump (queue *q) {
  if (q->size == 0) {
    printf("em_token queue is empty\n");
    return;
  }

  printf("queue dump:\n");

  for (int i = q->front; i < q->rear; i++) {
    char* type;

    switch (q->elements[i].type) {
      case EM_TOKEN_LITERAL: type = "li"; break;
      case EM_TOKEN_NEWLINE: type = "\\n"; break;
      case EM_TOKEN_EQ: type = "eq"; break;
      case EM_TOKEN_STRING: type = "st"; break;
      case EM_TOKEN_SPACE: type = "sp"; break;
      default: type = "??"; break;
    }

    printf("  %i: (%s) %s\n", i, type, q->elements[i].value);
  }
}
