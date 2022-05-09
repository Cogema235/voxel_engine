#include "render.h"

char    write_char(char chr, char end)
{
    write(STDOUT_FILENO, &chr, sizeof(char));
    write(STDOUT_FILENO, &end, sizeof(char));
    return chr;
}
char*   write_chars(char* buffer, int length, char end)
{
    for (int i = 0; i < length; i++)
    {
        write_char(buffer[i], 0);
    }
    write(STDOUT_FILENO, &end, sizeof(char));
    return buffer;
}
MATRIX* write_matrix(MATRIX* matrix, char sep, char end)
{
    for (int i = 0; i < matrix->x_size; i++)
    {
        for (int j = 0; j < matrix->y_size; j++)
        {
            write_char(matrix->cells[i][j], sep);
        }
        write(STDOUT_FILENO, "\n", sizeof(char));
    }
    write(STDOUT_FILENO, &end, sizeof(char));
    return matrix;
}
MATRIX* write_frame(MATRIX* matrix)
{
    system("clear");
    return write_matrix(matrix, ' ', '\n');
}
