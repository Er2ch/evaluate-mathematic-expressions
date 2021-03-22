#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "solve.h"
#include "lexer.h"

void parser(Node_s *node, size_t *status, Operator_s **operators)
{
    node->divider_pos = find_divider_pos(node->tokens, node->length, operators, status);
    if (node->divider_pos == -1)
        remove_brackets(node);
    
    node->divider_pos = find_divider_pos(node->tokens, node->length, operators, status);

    if (*status) return;
    if (node->divider_pos == -1) return;

    node->operator_sign = node->tokens[node->divider_pos]->value;
    node->left = new_node(node->tokens, node->divider_pos, NULL, NULL, '\0', 0);
    node->right = new_node(node->tokens + node->divider_pos + 1, node->length - node->divider_pos - 1, NULL, NULL, '\0', 0);


    parser(node->left, status, operators);
    parser(node->right, status, operators);
}

size_t find_divider_pos(Token_s **tokens, size_t tokens_count, Operator_s **opreators, size_t *status)
{
    int position = -1, brackets = 0, priority = 4;
    for (int i = tokens_count - 1; i >= 0; i--)
    {
        Token_s *current = tokens[i];

        if (current->type == t_brackets) 
        {
            if (current->value == '(') brackets++;
            else if (current->value == ')') brackets--;

            continue;
        }

        if (brackets != 0) continue;
        if (current->type != t_operators) continue;
        
        short current_priority = get_priority(current->value, opreators);

        if (current_priority == 1) return i;

        if (current_priority < priority)
        {
            priority = current_priority;
            position = i;
        }
    }

    return position;
}

short check_brackets(Node_s *node)
{
    size_t brackets = 0;
    if (node->tokens[0]->type != t_brackets || node->tokens[node->length - 1]->type != t_brackets) return 0;

    for (size_t i = 0; i < node->length; i++)
    {
        Token_s *current = node->tokens[i];

        if (current->type != t_brackets) continue;

        if (current->value == '(') brackets++;
        else if (current->value == ')') brackets--;

        if (brackets == 0 && i != node->length - 1) return 0;
    }

    return 1;
}

void remove_brackets(Node_s *node)
{
    while (check_brackets(node))
    {
        node->tokens++;
        node->length -= 2;
    }
}

Node_s *new_node(Token_s **tokens, size_t length, Node_s *left, Node_s *right, char operator_sign, size_t divider_pos)
{
    Node_s *result = (Node_s *)malloc(sizeof(Node_s));

    result->tokens = tokens;
    result->length = length;
    result->left = left;
    result->right = right;
    result->operator_sign = operator_sign;
    result->divider_pos = divider_pos;

    return result;
}

void free_tree(Node_s *node)
{
    if (node->left != NULL) free_tree(node->left);
    if (node->right != NULL) free_tree(node->right);

    free(node);
}