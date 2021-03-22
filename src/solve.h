#pragma once

typedef double(* operator_action_t)(double left, double right);

typedef struct Operator
{
    char sign;
    unsigned short priority;
    operator_action_t action;
} Operator_s;

#define OPERATORS_COUNT 7

#include "lexer.h"
#include "parser.h"

Operator_s *new_operator(char, unsigned short, operator_action_t);

short check_operator(char, Operator_s **);

short get_priority(char, Operator_s **);

double OP_add(double, double);
double OP_minus(double, double);
double OP_product(double, double);
double OP_division(double, double);
double OP_modulo(double, double);
double OP_int_division(double, double);
double OP_pow(double, double);

Operator_s **init_operators();

#ifndef MK_BLD
double solve(Node_s *, Operator_s **);
#endif
