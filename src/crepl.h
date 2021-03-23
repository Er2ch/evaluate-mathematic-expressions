#pragma once

#include <stdio.h> // for ssize_t

#define BUFF_SIZE 100
#define REPL_VER "3.0.0"

ssize_t write(int, const void *, size_t);
void REPL_run();
