#include "s21_matrix.h"

#include "utils.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return arithmetic(A, B, result, ADD);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return arithmetic(A, B, result, SUB);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int ret = OK;
  if (!is_correct(A) || !result) {
    ret = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return ret;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret = OK;
  if (!is_both_correct(A, B) || !result) {
    ret = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    ret = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    mul(A, B, result);
  }
  return ret;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int ret = SUCCESS;
  if (is_size_eq(A, B) == 0) {
    ret = FAILURE;
  }
  for (int i = 0; ret == SUCCESS && i < A->rows; i++) {
    for (int j = 0; ret == SUCCESS && j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
        ret = FAILURE;
      }
    }
  }
  return ret;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int ret = OK;
  if (result && rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
    }
  } else {
    ret = INCORRECT_MATRIX;
  }
  return ret;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
  }
}

int s21_determinant(matrix_t *A, double *result) {
  int ret = OK;
  if (!is_correct(A) || !result) {
    ret = INCORRECT_MATRIX;
  } else if (!is_square(A)) {
    ret = CALCULATION_ERROR;
  } else if (size(A) == 1) {
    *result = A->matrix[0][0];
  } else if (size(A) == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->columns; i++) {
      matrix_t m;
      s21_create_matrix(A->rows - 1, A->columns - 1, &m);
      minor(A, 0, i, &m);
      double r = 0;
      s21_determinant(&m, &r);
      *result += r * pow(-1, i) * A->matrix[0][i];
      s21_remove_matrix(&m);
    }
  }
  return ret;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = OK;
  if (!is_correct(A) || !result) {
    ret = INCORRECT_MATRIX;
  } else if (size(A) < 2) {
    ret = CALCULATION_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t m;
        s21_create_matrix(A->rows - 1, A->columns - 1, &m);
        minor(A, i, j, &m);
        double det = 0;
        ret = s21_determinant(&m, &det);
        result->matrix[i][j] = pow(-1, (i + j)) * det;
        s21_remove_matrix(&m);
      }
    }
  }
  return ret;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int ret = OK;
  if (!is_correct(A) || !result) {
    ret = INCORRECT_MATRIX;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return ret;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int ret = OK;
  if (!is_correct(A) || !result) {
    ret = INCORRECT_MATRIX;
  } else if (size(A) < 1) {
    ret = CALCULATION_ERROR;
  } else {
    double det = 0;
    s21_determinant(A, &det);
    if (size(A) == 1 && det != 0) {
      s21_create_matrix(A->rows, A->columns, result);
      result->matrix[0][0] = 1 / A->matrix[0][0];
    } else if (det != 0) {
      matrix_t M_compl = {0};
      s21_calc_complements(A, &M_compl);
      matrix_t M_compl_transposed = {0};
      s21_transpose(&M_compl, &M_compl_transposed);
      s21_mult_number(&M_compl_transposed, 1.0 / det, result);
      s21_remove_matrix(&M_compl);
      s21_remove_matrix(&M_compl_transposed);
    } else {
      ret = CALCULATION_ERROR;
    }
  }
  return ret;
}