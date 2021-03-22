#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "solve.h"

double solve(Node_s *, Operator_s **);

double solve(Node_s *node, Operator_s **operators)
{
    double left;
    double right;
    double result;

    if (node->left == NULL && node->right == NULL)
    {
        char *text = tokens_to_text(node->tokens, node->length);
        double result = atof(text);
        free(text);
        return result;
    }

    if (node->left->operator_sign == '\0')
    {
        char *leftt = tokens_to_text(node->left->tokens, node->left->length);
        left = atof(leftt);
        free(leftt);
    }
    else
        left = solve(node->left, operators);

    if (node->right->operator_sign == '\0')
    {
        char *rightt = tokens_to_text(node->right->tokens, node->right->length);
        right = atof(rightt);
        free(rightt);
    }
    else
        right = solve(node->right, operators);

    for (size_t i = 0; i < OPERATORS_COUNT; i++)
    {
        if (operators[i]->sign == node->operator_sign)
        {
            result = operators[i]->action(left, right);
            break;
        }
    }

    printf("%lf %c %lf = %lf\n", left, node->operator_sign, right, result);
    return result;
}

Operator_s *new_operator(char sign, unsigned short priority, operator_action_t action)
{
    Operator_s *result = (Operator_s *)malloc(sizeof(Operator_s));
    result->sign = sign;
    result->priority = priority;
    result->action = action;
    return result;
}

short check_operator(char _char, Operator_s **operators)
{
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
        if (operators[i]->sign == _char) 
            return 1;

    return 0;
}

short get_priority(char _char, Operator_s **operators)
{
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
        if (operators[i]->sign == _char) return operators[i]->priority;

    return -1;
}

double OP_add(double left, double right)
{ return left + right; }

double OP_minus(double left, double right)
{ return left - right; }

double OP_product(double left, double right) 
{ return left * right; }

double OP_division(double left, double right)
{ return left / right; }

double OP_modulo(double left, double right) 
{ return left - right * (int)(left / right);}

double OP_int_division(double left, double right)
{
  double x = left / right;
  int a = (int)x;
  if(x - a >= 0.5)
    if(a < 0) return a - 1;
    else return a + 1;
  else return a;
}

double OP_pow(double base, double exp)
{
  // https://stackoverflow.com/a/2892827
  if(exp == 0)
    return 1;
  if(exp < 0)
    return 1.0 / OP_pow(base, -exp);
  if((int)exp % 2 == 0) {
    double half_p = OP_pow(base, (int)(exp / 2));
    return half_p * half_p;
  }
  return base * OP_pow(base, exp - 1);
}

Operator_s **init_operators()
{
    Operator_s **operators = (Operator_s **)malloc(OPERATORS_COUNT * sizeof(Operator_s *));

    operators[0] = new_operator('+', 1, OP_add);
    operators[1] = new_operator('-', 1, OP_minus);
    operators[2] = new_operator('*', 2, OP_product);
    operators[3] = new_operator('/', 2, OP_division);
    operators[4] = new_operator('%', 2, OP_modulo);
    operators[5] = new_operator('\\', 2, OP_int_division);
    operators[6] = new_operator('^', 3, OP_pow);

    return operators;
}
