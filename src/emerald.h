#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>

// core
int start_repl ();
int parse_cli_arguments (int argc, char* argv[]);
void eval (char* filename);

// util
char* readfile (char filename[], int *fileSize);
void die (const char* format, ...);
void debug (char* msg);

// lexer
#define EM_EOF 0
#define EM_TOKEN_LITERAL 1
#define EM_TOKEN_NEWLINE 2
#define EM_TOKEN_EQ 3
#define EM_TOKEN_STRING 4
#define EM_TOKEN_SPACE 5
typedef struct em_token {
  int type;
  char* value;
} em_token;

  // has to be here
typedef struct queue {
  int capacity;
  int size;
  int front;
  int rear;
  em_token *elements;
} queue;

typedef struct em_lexer {
  int pos;
  int offset;
  int lineNumber;
  char* filename;
  char* source;
  em_token tok;
  queue* q;
} em_lexer;
void lexer_init (em_lexer* self, char* source, char* filename);
void lexer_scan (em_lexer* self);

// parser
#define EM_OP 0
#define EM_STRING 1
#define EM_LITERAL 2
void parse_buffer (char* buf, int size);
typedef struct node {
  
} node;

// queue
#define q_MAXELEMENTS 1000
queue* q_create ();
em_token q_dequeue (queue *q);
void q_enqueue (queue *q, em_token element);
void q_dump (queue *q);

