#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strlen

#include "calc.h"

Token_s **Lexer(char *expr, size_t *tok_cnt_ptr, size_t *status, Operator_s **oper) {
  size_t expr_len = strlen(expr), tok_cnt = 0;
  Token_s **tokens = calloc(expr_len, sizeof(Token_s*));

  Token_s *empty = Lex_token_new(t_none, '\0');

  for(size_t i = 0; i < expr_len; i++) {
    char curr = expr[i];
    Tokens_e type = t_none;
    Token_s *last;

    if(tok_cnt > 0)
      last = tokens[tok_cnt - 1];
    else last = empty;

    if(curr >= '0' && curr <= '9') {
      if(last->type != t_none && last->value != '(' && last->type != t_num && last->type != t_dot && last->type != t_op)
	*status = 1;
      type = t_num;
    }
    else if(VM_check_op(curr, oper)) {
      if(last->type != t_none && last->type != t_text && last->type != t_num && last->value != ')')
	*status = 1;
      type = t_op;
    }
    else if(curr == '.') {
      if(last->type != t_none && last->type != t_num && last->type != t_op)
	*status = 1;
      type = t_dot;
    }
    else if(curr == '(' || curr == ')') {
      if(last->type != t_none && ((curr == '(' && last->type != t_op && last->value != '(')
       || (curr == ')' && last->type != t_num && last->value != ')' && last->type != t_text)))
        *status = 1;
      type = t_brackets;
    }
    else if((curr >= 'a' && curr <= 'z') || (curr >= 'A' && curr <= 'Z')) {
      if(last->type != t_none && last->type != t_text && last->type != t_op)
	*status = 1;
      type = t_text;
    }
    else if(curr != ' ' && curr != '\n')
      *status = 1;

    if(*status) {
      Lex_unexpected(curr, i + 1);
      goto end;
    }

    if(type != t_none) {
      tokens[tok_cnt++] = Lex_token_new(type, curr);
      if(DEBUG) Lex_log(tokens[tok_cnt - 1]);
    }
  }
  goto end;
  
  end:
    free(empty);
    *tok_cnt_ptr = tok_cnt;
    tokens = realloc(tokens, tok_cnt * sizeof(Token_s*));
    return tokens;
}

Token_s *Lex_token_new(Tokens_e type, char value) {
  Token_s *tok = malloc(sizeof(Token_s));
  if(tok == NULL) {
    printf("Memory allocate error\n");
    exit(1);
  }
  tok->type = type;
  tok->value = value;
  return tok;
}

void Lex_unexpected(char token, size_t position) {
  printf("Unexpected token '%c' at %d\n", token, position);
}

void Lex_log(Token_s *token) {
  switch(token->type) {
    case t_num: printf("[NUM]"); break;
    case t_op: printf("[OPR]"); break;
    case t_dot: printf("[DOT]"); break;
    case t_brackets: printf("[BRK]"); break;
    case t_text: printf("[TXT]"); break;
  }
  printf(" %c\n", token->value);
}

char *Lex_tokens_to_text(Token_s **tokens, size_t length) {
  char *result = malloc(length * sizeof(char));

  for (size_t i = 0; i < length; i++)
    result[i] = tokens[i]->value;

  result[length] = '\0';
  return result;
}
