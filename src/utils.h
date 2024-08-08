#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "s21_matrix.h"

int is_size_eq(matrix_t *A, matrix_t *B);
int is_square(matrix_t *A);
int is_correct(matrix_t *A);
int is_both_correct(matrix_t *A, matrix_t *B);
int arithmetic(matrix_t *A, matrix_t *B, matrix_t *result, int action);
void mul(matrix_t *A, matrix_t *B, matrix_t *result);
void minor(matrix_t *A, int i, int j, matrix_t *result);
int size(matrix_t *A);

#endif