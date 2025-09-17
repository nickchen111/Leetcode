void freeMatrix(int** matrix, int colSize) {
    for (int i = 0; i < colSize; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {

    int** ans = (int**)malloc(matrixColSize[0] * sizeof(int*));
    for (int i = 0; i < matrixColSize[0]; i++) {
        ans[i] = (int*)malloc(matrixSize * sizeof(int));
    }

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[0]; j++) {
            ans[j][i] = matrix[i][j];
        }
    }

    *returnSize = matrixColSize[0];
    *returnColumnSizes = (int*)malloc(matrixColSize[0] * sizeof(int));
    for (int i = 0; i < matrixColSize[0]; i++) {
        (*returnColumnSizes)[i] = matrixSize;
    }
    return ans;
}