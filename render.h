//#pragma once
#ifndef RENDER_H_
#define RENDER_H_

#include <unistd.h>
#include <stdlib.h>
#include "matrix.h"

char    write_char(char chr, char end);
char*   write_chars(char* buffer, int length ,char end);
MATRIX* write_matrix(MATRIX* matrix, char sep, char end);
MATRIX* write_frame(MATRIX* matrix);

#endif /*!RENDER_H_*/