#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"
#include "crepl.h"

const char *REPL_intro =
  "Welcome to Calculator's REPL v." REPL_VER "\n"
  "Type \".exit\" to exit, \".help\" to more information."
#if DEBUG
  "\n" "DEBUG MODE"
#endif
  ;

const char *REPL_help =
  "Git repository: https://github.com/DemetryF/evaluate-mathematic-expressions"
  "\n\n"
  "7 operators: +, -, /, *, %%, \\, ^." "\n"
  "Brackets: \"()\"" "\n"
  "Double numbers: 2.1"
  ;

void REPL_run() {
  printf("%s\n", REPL_intro);

  size_t status = 0;
  char *input = calloc(BUFF_SIZE, sizeof(char));

  while (1) {
    memset(input, 0, BUFF_SIZE);
    size_t status = 0;
    write(1, "> ", 3); // musl support
    fgets(input, BUFF_SIZE, stdin);     

    // Ctrl-D
    if(!strcmp(input, "")) break;

    if(!strcmp(input, "\n")) 
      continue;

    if (input[0] == '.') {
      if (!strcmp(input + 1, "exit\n")) break;
      else if (!strcmp(input + 1, "help\n")) {
        printf("%s\n", REPL_help);
        continue;
      }
    }

    double result = VM_eval(input, &status);
    if (status) continue;

    printf("%g\n", result);
  }

  free(input);
}
