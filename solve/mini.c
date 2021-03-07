#pragma once

// https://stackoverflow.com/a/2892827
double pow(double base, double exp) {
  if(exp == 0)
    return 1;
  if(exp < 0)
    return 1.0 / pow(base, -exp);
  if((int)exp % 2 == 0) {
    double half_p = pow(base, (int)(exp / 2));
    return half_p * half_p;
  }
  return base * pow(base, exp - 1);
}

double mini(double left, double right, char op) {
  switch (op) {
    case '+': return left + right;
    case '-': return left - right;
    case '*': return left * right;
    case '/': return left / right;
    case '^': return pow(left, right);
  }
}