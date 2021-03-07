#pragma once

#include <stdlib.h>
#include "data.h"

void free_tree(Node_s *Head) {
  if (Head->left != NULL) free_tree(Head->left);
  if (Head->right != NULL) free_tree(Head->right);
  free(Head);
}