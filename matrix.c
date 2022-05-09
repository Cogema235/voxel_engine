#include "matrix.h"

MATRIX* create_matrix(int x_size_, int y_size_, float x_absolute_size_)
{
    MATRIX* matrix = malloc(sizeof(MATRIX));
    matrix->x_size = x_size_;
    matrix->y_size = y_size_;
    matrix->xmax = x_size_ - 1;
    matrix->ymax = y_size_ - 1;
    matrix->i_x0 = 0;
    matrix->j_y0 = 0;
    matrix->x_absolute_size = x_absolute_size_;
    matrix->cell_absolute_size = x_absolute_size_ / x_size_;
    matrix->cell_per_unit = x_size_ / x_absolute_size_;
    matrix->cells = malloc(x_size_ * sizeof(char*));
    for (int i = 0; i < x_size_; i++)
    {
        matrix->cells[i] = malloc(y_size_ * sizeof(char));
    }
    return matrix;
}

MATRIX* init_matrix(MATRIX* matrix, char value)
{
    for (int i = 0; i < matrix->x_size; i++)
    {
        for (int j = 0; j < matrix->y_size; j++)
        {
            matrix->cells[i][j] = value;
        }
    }
    return matrix;
}

MATRIX* clear_matrix(MATRIX* matrix)
{
    return init_matrix(matrix, 0);
}

MATRIX* resize_matrix(MATRIX* matrix, int new_x_size, int new_y_size)
{
    matrix->xmax += new_x_size - matrix->x_size;
    matrix->ymax += new_y_size - matrix->y_size;
    matrix->x_size = new_x_size;
    matrix->y_size = new_y_size;
    matrix->cells = realloc(matrix->cells, new_x_size * sizeof(char*));
    for (int i = 0; i < new_x_size; i++)
    {
        matrix->cells[i] = realloc(matrix->cells[i], new_y_size * sizeof(char));
    }
    return matrix;
}

MATRIX* replace_cells(MATRIX* matrix, char from, char to)
{
    for (int i = 0; i < matrix->x_size; i++)
    {
        for (int j = 0; j < matrix->y_size; j++)
        {
            matrix->cells[i][j] = (matrix->cells[i][j] == from) * to + (matrix->cells[i][j] != from) * matrix->cells[i][j];
        }
    }
    return matrix;
}

MATRIX* set_matrix_origin_abs(MATRIX* matrix, int new_x0, int new_y0)
{
    matrix->i_x0 = new_x0;
    matrix->j_y0 = new_y0;
    matrix->xmax = matrix->x_size - 1 - new_x0;
    matrix->ymax = matrix->y_size - 1 - new_y0;
    matrix->xmin = -new_x0;
    matrix->ymin = -new_y0;
    return matrix;
}

MATRIX* center_origin_matrix(MATRIX* matrix)
{
    return set_matrix_origin_abs(matrix, (int)(matrix->x_size / 2), (int)(matrix->y_size / 2));
}

MATRIX* set_cell(MATRIX* matrix, int x_, int y_,  char value)
{
    if (x_ <=  matrix->xmax && x_ >= matrix->xmin && y_ <= matrix->ymax && y_ >= matrix->ymin)
    {
        matrix->cells[matrix->i_x0 + x_][matrix->j_y0 + y_] = value;
        return matrix;
    }
    return (MATRIX*)NULL;
}

MATRIX* set_cell_absolute(MATRIX* matrix, float x_, float y_, char value)
{
    return set_cell(matrix, (int)(matrix->cell_per_unit * x_), (int)(matrix->cell_per_unit * y_), value);
}

char    get_cell(MATRIX* matrix, int x_, int y_)
{
    if (contains_cell(matrix, x_, y_))
    {
        return matrix->cells[matrix->i_x0 + x_][matrix->j_y0 + y_];
    }
    return 0;
}

char    get_cell_absolute(MATRIX* matrix, float x_, float y_)
{
    return get_cell(matrix, (int)(matrix->cell_per_unit * x_), (int)(matrix->cell_per_unit * y_));
}

int     contains_cell(MATRIX* matrix, int x_, int y_)
{
    return (x_ <=  matrix->xmax && x_ >= matrix->xmin && y_ <= matrix->ymax && y_ >= matrix->ymin);
}

int     contains_absolute_matrix_point(MATRIX* matrix, float x_, float y_) 
{
    return contains_cell(matrix, (int)(matrix->cell_per_unit * x_), (int)(matrix->cell_per_unit * y_));
}

void    destruct_matrix(MATRIX* matrix)
{
    for (int i = 0; i < matrix->x_size; i++)
    {
        free(matrix->cells[i]);
    }
    free(matrix->cells);
}
