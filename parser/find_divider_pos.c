size_t find_divider_pos(Lexem_s **lexems, size_t length) {
  size_t position = -1, brackets = 0, priority = 3;

  for (int i = 0; i < length; i++) {
    Lexem_s *current = lexems[i];

    if (current->Type == 4) {
      if (current->Data == '(') brackets++;
      else if (current->Data == ')') brackets--;
      continue;
    }

    if (brackets != 0) continue;
    if (current->Type != 3) continue;

    if (current->Data == '+' || current->Data == '-')
      return i;
    else if (current->Data == '/' || current->Data == '*') {
      position = i;
      priority = 2;
    }
    else if (current->Data == '^' && priority == 3)
      position = i;

  }

  if (brackets != 0) {
    printf("bracket error!\n");
    exit(1);
  }
  return position;
}