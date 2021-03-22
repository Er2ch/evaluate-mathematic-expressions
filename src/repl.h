#pragma once

#include <stdio.h>

double eval(char *, size_t *);

#define BUFF_SIZE 100
#define VERSION "3.0.0"

ssize_t write(int, const void *, size_t);

int main(size_t argc, char *argv[]);