#include <stdlib.h>

#include "lexer.h"
#include "parser.h"
#include "solve.h"
#include "repl.h"

double eval(char *expression, size_t *status)
{
    double result = 0.0;
    size_t tokens_count;
    Operator_s **operators = init_operators();
    Token_s **tokens = lexer(expression, &tokens_count, status, operators);

    if (*status)
        goto end;

    Node_s *head = new_node(tokens, tokens_count, NULL, NULL, 0, 0);
    parser(head, status, operators);

    if (*status)
        goto end;

    result = solve(head, operators);

  goto end;

  end:
    if (operators != NULL)
    {
      for (size_t i = 0; i < OPERATORS_COUNT; i++) free(operators[i]);
      free(operators);
    }

    if (tokens != NULL)
    {
      for (size_t i = 0; i < tokens_count; i++) free(tokens[i]);
      free(tokens);
    }

    if (head != NULL) free_tree(head);

    return result;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(size_t argc, char *argv[])
{
    printf("Welcome to Evaluate Mathematic Expression v%s\nType \".exit\" to exit, \".help\" to more information.\n", VERSION);

    char *input = calloc(BUFF_SIZE, sizeof(char));

    while (1)
    {
        memset(input, 0, BUFF_SIZE);
        size_t status = 0;
        write(1, "> ", 3); // musl support
        fgets(input, BUFF_SIZE, stdin);     

        if (strcmp(input, "\n") == 0) 
            continue;

        if (input[0] == '.')
        {
            if (strcmp(input + 1, "exit\n") == 0) break;
            if (strcmp(input + 1, "help\n") == 0) printf("Git repository: https://github.com/DemetryF/evaluate-mathematic-expressions\n\n7 operators: +, -, /, *, %%, \\, ^.\nBrackets: \"()\"\nDouble numbers: 2.1\n");

            continue;
        }

        double result = eval(input, &status);
        if (status) continue;

        printf("%g\n", result);
    }

    free(input);
    return 0;
}