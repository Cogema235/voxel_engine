//#pragma once
#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdlib.h>

typedef struct
{
    int    x_size;
    int    y_size;
    int    i_x0;
    int    j_y0;
    int    xmax;
    int    ymax;
    int    xmin;
    int    ymin;
    float  x_absolute_size;
    float  cell_absolute_size;
    float  cell_per_unit;
    char** cells;
}
MATRIX;

typedef struct
{
    float** cases;
    int     isize;
    int     jsize;
}
FMATRIX;

MATRIX* create_matrix(int x_size_, int y_size_, float x_absolute_size_);
MATRIX* init_matrix(MATRIX* matrix, char value);
MATRIX* phagocyte(MATRIX* predator, MATRIX* prey); /* definir aussi pour les espaces */
MATRIX* clear_matrix(MATRIX* matrix);
MATRIX* resize_matrix(MATRIX* matrix, int new_x_size, int new_y_size);
MATRIX* replace_cells(MATRIX* matrix, char from, char to);
MATRIX* set_matrix_origin_abs(MATRIX* matrix, int new_x0, int new_y0);
MATRIX* center_origin_matrix(MATRIX* matrix);
MATRIX* set_cell(MATRIX* matrix, int x_, int y_, char value);
MATRIX* set_cell_absolute(MATRIX* matrix, float x_, float y_, char value);
int     contains_abslute_matrix_point(float x_, float y_);
int     contains_cell(MATRIX* matrix, int x_, int y);
char    get_cell(MATRIX* matrix, int x_, int y_);
char    get_cell_absolute(MATRIX* matrix, float x_, float y_);
void    destruct_matrix(MATRIX* matrix);

FMATRIX* fmatrix(int isize_, int jsize_);
FMATRIX* set_cases(FMATRIX* matrix, float value);
FMATRIX* set_case(FMATRIX* matrix, int i, int j, float value);
FMATRIX* matrix_product(FMATRIX* A, FMATRIX* B);
float    get_case(FMATRIX* matrix, int i, int j);

/*
FMATRIX* fmatrix(int isize_, float jsize_)
{
    FMATRIX* matrix = malloc(sizeof(FMATRIX));
    matrix->isize = isize_;
    matrix->jsize = jsize_;
    matrix->cases = malloc(sizeof(float*) * isize_);
    for (int i = 0; i < isize_; i++)
    {
        matrix->cases[i] = malloc(sizeof(float) * jsize_);
    }
    return matrix;
}

FMATRIX* set_cases(FMATRIX* matrix, float value)
{
    for (int i = 0; i < matrix->isize; i++)
    {
        for (int j = 0; j < matrix->jsize; j++)
        {
            matrix->cases[i][i] = value;
        }
    }
    return matrix;
}

FMATRIX* set_case(FMATRIX* matrix, int i, int j, float value)
{
    matrix->cases[i][j] = value;
    return matrix;
}

FMATRIX* matrix_product(FMATRIX* A, FMATRIX* B)
{
    FMATRIX* composee = fmatrix()
}

float get_case(FMATRIX* matrix, int i, int j)
{
    return matrix->cases[i][j];
}
*/

#endif /*!MATRIX_H_*/