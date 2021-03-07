#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/lexer.c"
#include "lexer/data.h"
#include "lexer/check_valid.c"

#include "parser/data.h"
#include "parser/parser.c"
#include "parser/free_tree.c"

#include "solve/solve.c"

#include "repl.c"

// Entry point

int main(int argc, char const *argv[]) {
  repl(); // TODO: Add help, args, etc...
  return 0;
}