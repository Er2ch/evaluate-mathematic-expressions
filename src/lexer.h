#pragma once

typedef enum
{
    t_number,
    t_operators,
    t_decimal_seporator,
    t_brackets,
    t_text,
    t_none
} Tokens_e;

typedef struct
{
    Tokens_e type;
    char value;
} Token_s;

#include "solve.h"

Token_s *new_token(Tokens_e type, char value);

void lexer_unexped_token(char token, size_t position);

void lexer_log(Token_s *token);

char *tokens_to_text(Token_s **tokens, size_t length);

Token_s **lexer(char *expression, size_t *tokens_count_ptr, size_t *status, Operator_s **operators);
