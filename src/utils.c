#include "utils.h"

#include "s21_matrix.h"

int is_size_eq(matrix_t *A, matrix_t *B) {
  int ret = 0;
  if (is_both_correct(A, B)) {
    ret = A->rows == B->rows && A->columns == B->columns;
  }
  return ret;
}

int is_square(matrix_t *A) { return (A->rows == A->columns); }

int size(matrix_t *A) {
  int ret = 0;
  if (!is_square(A)) {
    ret = -1;
  } else {
    ret = A->rows;
  }
  return ret;
}

int is_correct(matrix_t *A) {
  int ret = 1;
  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1) {
    ret = 0;
  }
  return ret;
}

int is_both_correct(matrix_t *A, matrix_t *B) {
  return is_correct(A) && is_correct(B);
}

int arithmetic(matrix_t *A, matrix_t *B, matrix_t *result, int action) {
  int ret = OK;
  if (!is_both_correct(A, B) || !result) {
    ret = INCORRECT_MATRIX;
  } else if (!is_size_eq(A, B)) {
    ret = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + (B->matrix[i][j] * action);
      }
    }
  }
  return ret;
}

void mul(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
}

void minor(matrix_t *A, int i, int j, matrix_t *result) {
  for (int li = 0; li < A->rows; li++) {
    if (li == i) {
      continue;
    }
    for (int lj = 0; lj < A->columns; lj++) {
      if (lj == j) {
        continue;
      }
      result->matrix[li - (li > i)][lj - (lj > j)] = A->matrix[li][lj];
    }
  }
}