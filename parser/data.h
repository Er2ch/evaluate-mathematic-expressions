#include "../lexer/data.h"

#pragma once

// TODO: Change this shit
typedef struct Node Node_s;

struct Node {
  Lexem_s **lexems;
  Node_s *left;
  Node_s *right;
  char Operator;
  size_t length;
  size_t divider_pos;
};

Node_s *new_node(
  Lexem_s **lexems,
  size_t length,
  size_t divider_pos,
  char Operator,
  Node_s *left,
  Node_s *right
) {


  Node_s *node = (Node_s *)malloc(sizeof(Node_s));

  node->lexems = lexems;
  node->length = length;
  node->divider_pos = divider_pos;
  node->Operator = Operator;
  node->left = left;
  node->right = right;

  return node;
}