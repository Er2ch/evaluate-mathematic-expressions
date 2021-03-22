#pragma once
#define MK_BLD

#include "lexer.h"

typedef struct Node
{
    struct Node *left;
    struct Node *right;
    Token_s **tokens;
    char operator_sign;
    size_t divider_pos;
    size_t length;
} Node_s;

#undef MK_BLD

Node_s *new_node(Token_s **, size_t, Node_s *, Node_s *, char, size_t);

size_t find_divider_pos(Token_s **, size_t, Operator_s **, size_t *);

short check_brackets(Node_s *);

void remove_brackets(Node_s *);

void free_tree(Node_s *);

void parser(Node_s *, size_t *, Operator_s **);