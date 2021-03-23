#pragma once

#ifndef DEBUG
#define DEBUG 0
#endif

#include <stdio.h>

typedef enum {
  t_num,
  t_op,
  t_dot,
  t_brackets,
  t_text,
  t_none
} Tokens_e;

typedef struct {
  Tokens_e type;
  char value;
} Token_s;

typedef double(* operator_action_t)(double left, double right);

typedef struct {
  char sign;
  unsigned short priority;
  operator_action_t action;
} Operator_s;

typedef struct Node {
  struct Node *left;
  struct Node *right;
  Token_s **tokens;
  char op;
  size_t div_pos;
  size_t len;
} Node_s;

#define OPERATORS_COUNT 7

// lexer

Token_s **Lexer(char *, size_t *, size_t *, Operator_s **);

Token_s *Lex_token_new(Tokens_e, char);

void Lex_unexpected(char, size_t);

void Lex_log(Token_s *);

char *Lex_tokens_to_text(Token_s **, size_t);

// parser

Node_s *Par_new_node(Token_s **, size_t, Node_s *, Node_s *, char, size_t);

size_t Par_div_pos(Token_s **, size_t, Operator_s **, size_t *);

short Par_chk_brackets(Node_s *);

void Par_rem_brackets(Node_s *);

void Par_free_tree(Node_s *);

void Parser(Node_s *, size_t *, Operator_s **);

// solve

Operator_s *VM_new_op(char, unsigned short, operator_action_t);

short VM_check_op(char, Operator_s **);

short VM_get_priority(char, Operator_s **);

double OP_add(double, double);
double OP_minus(double, double);
double OP_product(double, double);
double OP_division(double, double);
double OP_modulo(double, double);
double OP_int_division(double, double);
double OP_pow(double, double);

Operator_s **VM_init_ops();

double VM_eval(char *, size_t *);

double VM(Node_s *, Operator_s **);
