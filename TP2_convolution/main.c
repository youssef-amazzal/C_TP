#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **get_random_matrice(int N);
int trace_matrice(int **matrice, int size);
int getSubSize(int size);
void printMatrice(int **mat, int size, char *label);
int **conv_matrices(int **matA, int size, int **matB);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);

    int **matrice = get_random_matrice(N);
    int **kernel = get_random_matrice(getSubSize(N));

    int **result = conv_matrices(matrice, N, kernel);

    printMatrice(matrice, N, "A");
    printMatrice(kernel, getSubSize(N), "B");
    printMatrice(result, N, "C");

    return 0;
}

int **get_random_matrice(int N)
{
    int **array = malloc(N * sizeof(int *));

    for (int i = 0; i < N; i++)
    {
        array[i] = malloc(N * sizeof(int));
    }

    srand(time(NULL));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            array[i][j] = rand() % 10;
        }
    }

    return array;
}

int trace_matrice(int **matrice, int size)
{
    int trace = 0;

    for (int i = 0; i < size; i++)
    {
        trace += matrice[i][i];
    }

    return trace;
}

int **conv_matrices(int **matA, int size, int **matB)
{
    int startI, startJ, endI, endJ;
    int sizeA = size;
    int sizeB = getSubSize(size);

    int offset = sizeB / 2;

    int **matC = malloc(sizeA * sizeof(int *));
    for (int i = 0; i < sizeA; i++)
    {
        matC[i] = malloc(sizeA * sizeof(int));
    }

    for (int i = 0; i < sizeA; i++)
    {
        startI = offset - i >= 0 ? offset - i : 0;
        endI = sizeA - i + offset <= sizeB ? sizeA - i + offset : sizeB;

        for (int j = 0; j < sizeA; j++)
        {
            startJ = offset - j >= 0 ? offset - j : 0;
            endJ = sizeA - j + offset <= sizeB ? sizeA - j + offset : sizeB;

            matC[i][j] = 0;

            for (int k = startI; k < endI; k++)
            {

                for (int l = startJ; l < endJ; l++)
                {
                    matC[i][j] += matA[i + (k - offset)][j + (l - offset)] * matB[k][l];
                }
            }
        }
    }

    return matC;
}

int getSubSize(int size)
{
    return 2 * (size / 3) + 1;
}

void printMatrice(int **mat, int size, char *label)
{
    printf("Matrice: %s(%d,%d)\n\n", label, size, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%-5d", mat[i][j]);
        }

        printf("\n");
    }

    printf("\n\n");
}