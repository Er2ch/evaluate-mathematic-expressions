#include <stdlib.h>

#pragma once

struct Lexem {
  char Data;
  int Type;
};

typedef struct Lexem Lexem_s;

Lexem_s *new_lexem(char Data, int Type) {
  Lexem_s *lexem = (Lexem_s*)malloc(sizeof(Lexem_s));
  lexem->Data = Data;
  lexem->Type = Type;
  return lexem;
}

char *lexems_to_text(Lexem_s **lexems, size_t length) {
  char *result = malloc(length * sizeof(char));
  size_t size;
  for (size = 0; size < length; size++) result[size] = lexems[size]->Data;
  result[size++] = '\0';
  return result;
}