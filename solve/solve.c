#include <stdio.h>
#include <stdlib.h>

#pragma once

#include "../parser/data.h"
#include "../lexer/data.h"

#include "mini.c"

double solve(Node_s *node) {
  if (node->left == NULL && node->right == NULL) {
    char *text = lexems_to_text(node->lexems, node->length);
    double result = atof(text);
    free(text);
    return result;
  } 
  else if (node->left->left == NULL
   && node->left->right == NULL 
   && node->right->left == NULL
   && node->right->right == NULL)
  {
    char *leftT = lexems_to_text(node->left->lexems, node->left->length);
    char *rightT = lexems_to_text(node->right->lexems, node->right->length);

    double leftN = atof(leftT);
    double rightN = atof(rightT);

    free(leftT);
    free(rightT);

    return mini(leftN, rightN, node->Operator);
  }
  else if (node->left->left == NULL
   && node->left->right == NULL)
  {
    char *T = lexems_to_text(node->left->lexems, node->left->length);
    double N = atof(T);
        
    free(T);

    return mini(N, solve(node->right), node->Operator);
  }
  else if (node->right->left == NULL
   && node->right->right == NULL)
  {
    char *T = lexems_to_text(node->right->lexems, node->right->length);
    double N = atof(T);
        
    free(T);

    return mini(solve(node->left), N, node->Operator);
  } else
    return mini(solve(node->left), solve(node->right), node->Operator);
}