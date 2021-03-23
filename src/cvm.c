#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc.h"

double VM(Node_s *node, Operator_s **ops) {
  double left, right, result;

  if(node->left == NULL && node->right == NULL) {
    char *text = Lex_tokens_to_text(node->tokens, node->len);
    result = atof(text);
    free(text);
    return result;
  }

  if(node->left->op == '\0') {
    char *leftt = Lex_tokens_to_text(node->left->tokens, node->left->len);
    left = atof(leftt);
    free(leftt);
  } else left = VM(node->left, ops);

  if(node->right->op == '\0') {
    char *rightt = Lex_tokens_to_text(node->right->tokens, node->right->len);
    right = atof(rightt);
    free(rightt);
  } else right = VM(node->right, ops);

  for(int i = 0; i < OPERATORS_COUNT; i++) {
    if(ops[i]->sign == node->op) {
      result = ops[i]->action(left, right);
      break;
    }
  }

  if(DEBUG) printf("%lf %c %lf = %lf\n", left, node->op, right, result);
  return result;
}

double VM_eval(char *expr, size_t *status) {
  double result = 0.0;
  size_t tokens_count;
  Node_s *head = NULL;
  Operator_s **ops = VM_init_ops();
  Token_s **tokens = Lexer(expr, &tokens_count, status, ops);

  if (*status)
    goto end;

  head = Par_new_node(tokens, tokens_count, NULL, NULL, '\0', 0);
  Parser(head, status, ops);

  if (*status)
    goto end;

  result = VM(head, ops);

  goto end;

  end:
    if (ops != NULL) {
      for (size_t i = 0; i < OPERATORS_COUNT; i++)
        free(ops[i]);
      free(ops);
    }

    if (tokens != NULL) {
      for (size_t i = 0; i < tokens_count; i++)
        free(tokens[i]);
      free(tokens);
    }

    if (head != NULL)
      Par_free_tree(head);

    return result;
}

Operator_s **VM_init_ops() {
  Operator_s **ops = malloc(OPERATORS_COUNT * sizeof(Operator_s *));

  ops[0] = VM_new_op('+', 1, OP_add);
  ops[1] = VM_new_op('-', 1, OP_minus);
  ops[2] = VM_new_op('*', 2, OP_product);
  ops[3] = VM_new_op(':', 2, OP_division);
  ops[4] = VM_new_op('%', 2, OP_modulo);
  ops[5] = VM_new_op('/', 2, OP_int_division);
  ops[6] = VM_new_op('^', 3, OP_pow);

  return ops;
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

double OP_int_division(double left, double right) {
  double x = left / right;
  int a = (int)x;
  if(x - a >= 0.5)
    if(a < 0) return a - 1;
    else return a + 1;
  else return a;
}

double OP_pow(double base, double exp) {
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

Operator_s *VM_new_op(char sign, unsigned short priority, operator_action_t action) {
  Operator_s *result = malloc(sizeof(Operator_s));
  result->sign = sign;
  result->priority = priority;
  result->action = action;
  return result;
}

short VM_check_op(char _char, Operator_s **ops) {
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
        if (ops[i]->sign == _char) 
            return 1;

    return 0;
}

short VM_get_priority(char _char, Operator_s **ops) {
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
        if (ops[i]->sign == _char) return ops[i]->priority;

    return -1;
}