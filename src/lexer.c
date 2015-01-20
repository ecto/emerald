#include "emerald.h"


void lexer_init (em_lexer* self, char* source, char* filename) {
  self->pos = -1;
  self->offset = 0;
  self->lineNumber = 0;
  self->source = source;
  self->filename = filename;
  self->q = q_create();
}

static char nextChar (em_lexer* self) {
  self->pos++;
  return self->source[self->pos];
}

/*
static char prevChar (em_lexer* self) {
  self->pos--;
  return self->source[self->pos];
}
*/

#define current self->source[self->pos]
#define next self->source[self->pos + offset]
#define nextIsAcceptableLiteral isalpha(next) || isdigit(next)
static int scan_literal (em_lexer* self, int ch) {
  self->tok.type = EM_TOKEN_LITERAL;
  char buf[128];
  int offset = 0;

  while (isalpha(self->source[self->pos + offset])) {
    buf[offset] = self->source[self->pos + offset];
    offset++;
  }

  buf[offset] = '\0';
  self->tok.value = strdup(buf);
  self->pos += offset - 1;

  return 0;
}

static int scan_string (em_lexer* self, int ch) {
  self->tok.type = EM_TOKEN_STRING;
  self->pos++;
  char buf[128];
  int offset = 0;

  while (next != '"' && next != '\'') {
    buf[offset] = self->source[self->pos + offset];
    offset++;
  }

  buf[offset] = '\0';
  self->tok.value = strdup(buf);
  self->pos += offset;

  return 0;
}

static int scan_number (em_lexer* self, int c) {
  self->tok.type = EM_TOKEN_LITERAL;
  char buf[128];
  int offset = 0;

  while (isalpha(self->source[self->pos + offset])) {
    buf[offset] = self->source[self->pos + offset];
    offset++;
  }

  buf[offset] = '\0';
  self->tok.value = strdup(buf);
  self->pos += offset;

  return 0;
}

static void lexer_push (em_lexer* self) {
  q_enqueue(self->q, self->tok);
  self->tok.value = NULL;
}

static int lexer_step (em_lexer* self, char ch) {
  switch (ch) {
    case EM_EOF: die("end of token stream");
    case ' ':
      self->tok.type = EM_TOKEN_SPACE;
      break;
    case '"':
    case '\'':
      return scan_string(self, ch);
      break;
    case '\n':
      self->lineNumber++;
      self->tok.type = EM_TOKEN_NEWLINE;
      break;
    case '=':
      self->tok.type = EM_TOKEN_EQ;
      break;
    default:
      if (isalpha(ch)) {
        return scan_literal(self, ch);
      }

      if (isdigit(ch)) {
        return scan_number(self, ch);
      }

      die("%s: line %i: unknown character: %c (%i)", self->filename, self->lineNumber, ch, ch);
  }

  return 0;
}

void lexer_scan (em_lexer* self) {
  char ch;

  while ((ch = nextChar(self)) != EM_EOF) {
    lexer_step(self, ch);
    lexer_push(self);
  }

  q_dump(self->q);
}
