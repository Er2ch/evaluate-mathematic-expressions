#include <stdio.h>
#include <stdlib.h>

#pragma once

#include "../lexer/data.c"
#include "data.c"
#include "find_divider_pos.c"

void parser(Node_s *node) { // No comments...
  node->divider_pos = find_divider_pos(node->lexems, node->length);

  if (node->divider_pos == -1) {
    if (
     node->lexems[0]->Data == '('
     && node->lexems[node->length - 1]->Data == ')'
    ) {
      while (node->divider_pos == -1) {
        if (node->lexems[0]->Data == '(' && node->lexems[node->length - 1]->Data == ')') {
          node->lexems++;
          node->length -= 2;
          node->divider_pos = find_divider_pos(node->lexems, node->length);
        } else break;
      }
    }
    else {
      node->divider_pos = find_divider_pos(node->lexems, node->length);
      node->left = NULL;
      node->right = NULL;
      return;
    }
  }
  if (node->divider_pos == -1) {
    node->left = NULL;
    node->right = NULL;
    return;
  }

  node->left = (Node_s *)malloc(sizeof(Node_s));
  node->right = (Node_s *)malloc(sizeof(Node_s));

  node->Operator = node->lexems[node->divider_pos]->Data;

  node->left->lexems = node->lexems;
  node->right->lexems = node->lexems + (node->divider_pos + 1);

  node->left->length = node->divider_pos;
  node->right->length = node->length - node->divider_pos - 1;

  parser(node->left);
  parser(node->right);
}