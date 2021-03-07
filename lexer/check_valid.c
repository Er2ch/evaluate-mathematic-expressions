#include <stdio.h>
#include <stdlib.h>

#pragma once

#include "data.h"
#include "lexer.c"

short check_valid(Lexem_s **lexems, size_t length) {
  for (int i = 1; i < length; i++) {
    Lexem_s *current = lexems[i];
    Lexem_s *last = lexems[i - 1];

    if (
     (current->Type == 1 && last->Data == ')') // check numbers
     || (current->Type == 2 && last->Type != 1) // check decimal separators (.)
     || (current->Type == 3 && (last->Type != 1 && last->Data != ')')) // check operators
     || (current->Type == 4 && (current->Data == '(' && last->Type != 3 && last->Data != '(') // check brackets
     || (current->Data == ')' && (last->Type != 1 && last->Data != ')')))
    ) return lexer_error(current->Data, i);

  }
  return 0;
}