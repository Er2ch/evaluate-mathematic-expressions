// Include from main.c as last file!

#pragma once

#define MAX_TEXT_SIZE 100
#define GH_REPO_URL "https://github.com/DemetryF/evaluate-mathematic-expressions"
#define REPL_VER "2.1"

double eval(char* expression) {
  // printf("\nLexing...\n\n");

  size_t lexemsCount;
  Lexem_s **lexems = lexer(expression, &lexemsCount);

  if ((unsigned)lexems == 1) return (unsigned)-1;

  char* lx_result = lexems_to_text(lexems, lexemsCount);

  // printf("\nlexing result: '%s', lexems count: %ld\n", lx_result, lexemsCount);
  free(lx_result);

  // printf("\nparsing...\n\n");

  Node_s *Head = new_node(lexems, lexemsCount, -1, '\0', 0x0, 0x0);
  if (check_valid(Head->lexems, Head->length)) return (unsigned)-1;
  parser(Head);

  double result = solve(Head);

  for (int i = 0; i < lexemsCount; i++) free(lexems[i]);
  free(lexems);
  free_tree(Head);

  return result;
}

// Entry point

void repl() {
  char expr[MAX_TEXT_SIZE]; // String (array of chars)

  printf("Welcome to REPL v.%s!\nSource repository: %s\nType \".exit\" for exit to console.\n", REPL_VER, GH_REPO_URL);

  while(1) {
    printf("> ");
    fgets(expr, MAX_TEXT_SIZE, stdin); // Await for expression

    if (strcmp(expr, ".exit\n") == 0) exit(0);
    if (strcmp(expr, "\n\0") == 0) continue;

    double result = eval(expr); // Eval
    if(result == (unsigned)-1) continue; // R.I.P.
    printf(">> %lf\n", result); // Print result
  }
}
