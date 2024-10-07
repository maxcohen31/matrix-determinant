/*
    C program to compute the determinant of a nxn matrix recursively using Laplace expansion.

    Reference: https://en.wikipedia.org/wiki/Laplace_expansion

    Author: Abbate Emanuele
    Date: 06/10/2024

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void fail(int **m)
{
    if (m == NULL) 
    {
        exit(EXIT_FAILURE);
    }
}

int determinant(int **matrix, int n)
{ 
    // base case - 1x1 matrix   
    if (n == 1)
    {
        return matrix[0][0];
    }

    // base case - 2x2 matrix 
    if (n == 2)
    {
        return (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
    }

    int result = 0;

    for (int i = 0; i < n; i++)
    {
        // allocating memory for submatrix B
        int **sub_matrix = (int**)malloc((n-1)*sizeof(int*));
        for (int j = 0; j < n - 1; j++)
        {   
            sub_matrix[j] = (int*)malloc((n-1)*sizeof(int));
        }
        fail(sub_matrix);

        // excluding first row and column i
        for (int sub_row = 1; sub_row < n; sub_row++)
        {
            // lines 58-61
            // https://stackoverflow.com/questions/59121487/how-do-i-implement-the-laplace-expansion-algorithm-in-c
            int sub_col = 0; // column of submatrix
            for (int k = 0; k < n; k++)
            {
                if (k == i) 
                {
                    continue;
                }
                sub_matrix[sub_row-1][sub_col++] = matrix[sub_row][k];
            }

            result += ((i % 2 == 0) ? 1 : -1) * matrix[0][i] * determinant(sub_matrix, n-1); 
        }

        for (int j = 0; j < n; j++)
        {
            free(sub_matrix[j]);
        }

        free(sub_matrix);
    
    }
    return result;
}

int main(int argc, char *argv[])
{
    int row;
    int col;

    printf("Insert rows -> ");
    scanf("%d", &row);

    printf("Insert columns -> ");
    scanf("%d", &col);

    if (row != col) 
    {
        printf("Rows and columns must be the same size!");
        exit(EXIT_FAILURE);
    }

    int **mat = (int**)malloc(row*sizeof(int*));
    for (int i = 0; i < row; i++)
    {
        mat[i] = (int*)malloc(col*sizeof(int));
    }
    fail(mat);

    // ask the user to insert entries
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int element;
            printf("insert element at position [%d][%d]: ", i+1, j+1);
            scanf("%d", &element);
            mat[i][j] = element; 
        }
    }

    int det = determinant(mat, row);
    printf("Determinant is equal to: %d\n", det); 

    // deallocate memory
    for (int i = 0; i < row; i++)
    {
        free(mat[i]);
    }
    free(mat);

    return 0;
}
