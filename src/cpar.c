#include <stdio.h>
#include <stdlib.h>

#include "calc.h"

void Parser(Node_s *node, size_t *status, Operator_s **ops) {
  if(
   (node->div_pos = Par_div_pos(node->tokens, node->len, ops, status))
   == -1
  ) {
    Par_rem_brackets(node);
    node->div_pos = Par_div_pos(node->tokens, node->len, ops, status);
  }
  if(*status || node->div_pos == -1) return;

  node->op = node->tokens[node->div_pos]->value;
  node->left = Par_new_node(node->tokens, node->div_pos, NULL, NULL, '\0', 0);
  node->right = Par_new_node(node->tokens + node->div_pos + 1, node->len - node->div_pos - 1, NULL, NULL, '\0', 0);

  Parser(node->left, status, ops);
  Parser(node->right, status, ops);
}

size_t Par_div_pos(Token_s **tokens, size_t tok_cnt, Operator_s **ops, size_t *status) {
  int pos = -1, brk = 0, pr = 4;
  for(int i = tok_cnt - 1; i >= 0; i--) {
    Token_s *curr = tokens[i];

    if(curr->type == t_brackets) {
      if(curr->value == '(') brk++;
      else if(curr->value == ')') brk--;
      continue;
    }

    if(brk != 0) continue;
    if(curr->type != t_op) continue;

    short curr_pr = VM_get_priority(curr->value, ops);

    if(curr_pr == 1) return i;

    if(curr_pr < pr) {
      pr = curr_pr;
      pos = i;
    }
  }

  return pos;
}

short Par_chk_brackets(Node_s *node) {
  size_t brk = 0;
  if (node->tokens[0]->type != t_brackets || node->tokens[node->len - 1]->type != t_brackets)
    return 0;

  for (size_t i = 0; i < node->len; i++) {
    Token_s *curr = node->tokens[i];

    if (curr->type != t_brackets) continue;

    if (curr->value == '(') brk++;
    else if (curr->value == ')') brk--;

    if (brk == 0 && i != node->len - 1)
      return 0;
  }
  return 1;
}

void Par_rem_brackets(Node_s *node) {
  while (Par_chk_brackets(node)) {
    node->tokens++;
    node->len -= 2;
  }
}

Node_s *Par_new_node(
  Token_s **tokens,
  size_t len,
  Node_s *left,
  Node_s *right,
  char op,
  size_t div_pos
) {
  Node_s *n = malloc(sizeof(Node_s));

  n->tokens = tokens;
  n->len = len;
  n->left = left;
  n->right = right;
  n->op = op;
  n->div_pos = div_pos;

  return n;
}

void Par_free_tree(Node_s *node) {
  if(node == NULL) return;

  if (node->left != NULL) Par_free_tree(node->left);
  if (node->right != NULL) Par_free_tree(node->right);

  free(node);
}