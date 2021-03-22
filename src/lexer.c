#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen

#include "lexer.h"
#include "solve.h"

Token_s **lexer(char *expression, size_t *tokens_count_ptr, size_t *status, Operator_s **operators)
{
    size_t expression_length = strlen(expression),
        tokens_count = 0;
    Token_s **tokens = (Token_s **)calloc(expression_length, sizeof(Token_s *));

    Token_s *empty_token = new_token(t_none, '\0');

    for (size_t i = 0; i < expression_length; i++)
    {
        char current = expression[i];
        Tokens_e type = t_none;
        Token_s *last;

        if (tokens_count > 0)
            last = tokens[tokens_count - 1];
        else 
            last = empty_token;

        if (current >= '0' && current <= '9')
        {
            if (last->type != t_none && last->value != '(' && last->type != t_number && last->type != t_decimal_seporator && last->type != t_operators) 
                *status = 1; 
            type = t_number;
        }
        else if (check_operator(current, operators))
        {
            if (last->type != t_none && last->type != t_text && last->type != t_number && last->value != ')') 
                *status = 1;
            type = t_operators;
        }
        else if (current == '.')
        {
            if (last->type != t_none && last->type != t_number) 
                *status = 1;
            type = t_decimal_seporator;
        }
        else if (current == '(' || current == ')')
        {
            if (last->type != t_none && ((current == '(' && last->type != t_operators && last->value != '(') ||
                 (current == ')' && last->type != t_number && last->value != ')' && last->type != t_text))) 
                 *status = 1;
            type = t_brackets;
        }
        else if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z'))
        {
            if (last->type != t_none && last->type != t_text && last->type != t_operators) 
                *status = 1;
            type = t_text;
        }
        else if (current != ' ' && current != '\n')
            *status = 1;

        if (*status)
        {
            lexer_unexped_token(current, i);
            *tokens_count_ptr = tokens_count;
            free(empty_token);
            return tokens;
        }

        if (type != t_none)
        {
            tokens[tokens_count] = new_token(type, current);
            // lexer_log(tokens[tokens_count]);
            tokens_count++;
        }
    }
    free(empty_token);
    *tokens_count_ptr = tokens_count;
    tokens = (Token_s **)realloc(tokens, tokens_count * sizeof(Token_s *));
    return tokens;
}

Token_s *new_token(Tokens_e type, char value)
{
    Token_s *result = (Token_s *)malloc(sizeof(Token_s));

    if (result == NULL)
    {
        printf("allocate memory error.\n");
        exit(1);
    }

    result->type = type;
    result->value = value;

    return result;
}

void lexer_unexped_token(char token, size_t position)
{
    printf("unexpected token '%c' at %d\n", token, position);
}

void lexer_log(Token_s *token)
{
    switch (token->type)
    {
        case t_number:              printf("[       NUMBER       ]"); break;
        case t_operators:           printf("[      OPERATOR      ]"); break;
        case t_decimal_seporator:   printf("[ DECIMAL  SEPARATOR ]"); break;
        case t_brackets:            printf("[      BRACKETS      ]"); break;
        case t_text:                printf("[        TEXT        ]"); break;
    }

    printf(" %c\n", token->value);
}

char *tokens_to_text(Token_s **tokens, size_t length)
{
    char *result = malloc(length * sizeof(char));

    for (size_t i = 0; i < length; i++)
        result[i] = tokens[i]->value;

    result[length] = '\0';

    return result;
}
