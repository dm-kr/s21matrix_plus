#include "s21_test.h"

START_TEST(matrix_mult_mtrx_test_1) {
  double array_a[3][2] = {{1, 4}, {2, 5}, {3, 6}};
  double array_b[2][3] = {{1, -1, 1}, {2, 3, 4}};
  double array_res[3][3] = {{9, 11, 17}, {12, 13, 22}, {15, 15, 27}};
  int row_a = 3;
  int col_a = 2;
  int row_b = 2;
  int col_b = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  matrix_t res_check = {0};
  s21_create_matrix(row_a, col_a, &A);
  s21_create_matrix(row_b, col_b, &B);
  s21_create_matrix(row_a, col_b, &res_check);
  for (int i = 0; i < row_a; i++) {
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  for (int i = 0; i < res_check.rows; i++) {
    for (int j = 0; j < res_check.columns; j++) {
      res_check.matrix[i][j] = array_res[i][j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&res_check, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_mult_mtrx_test_2) {
  double array_a[3][5] = {{2.36, 4.59, 4.325, 0.364, 0.003},
                          {2.3, 99.6, 45.786, 944.36, 23.336},
                          {-5546, -2.36, -31.668, -565.22, -94.2}};
  double array_b[2][3] = {{2, 5, 7}, {6, 3, 4}};
  int row_a = 3;
  int col_a = 5;
  int row_b = 2;
  int col_b = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(row_a, col_a, &A);
  s21_create_matrix(row_b, col_b, &B);
  s21_create_matrix(row_a, col_b, &result);
  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < row_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_mult_mtrx_test_3) {
  double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row_b = 3;
  int col_b = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(row_b, col_b, &B);
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_mult_mtrx_test_4) {
  double array_a[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row_a = 3;
  int col_a = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(row_a, col_a, &A);
  for (int i = 0; i < row_a; i++) {
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(matrix_mult_mtrx_test_5) {
  double array_b[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_a[2][3] = {{2, 5, 7}, {6, 3, 4}};
  int row_b = 3;
  int col_b = 3;
  int row_a = 2;
  int col_a = 3;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(row_a, col_a, &A);
  s21_create_matrix(row_b, col_b, &B);
  for (int i = 0; i < row_a; i++)
    for (int j = 0; j < col_a; j++) {
      A.matrix[i][j] = array_a[i][j];
    }
  for (int i = 0; i < row_b; i++) {
    for (int j = 0; j < col_b; j++) {
      B.matrix[i][j] = array_b[i][j];
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_s21_mult_matrix(void) {
  Suite *s = suite_create("\033[42mS21_MULT_MATRIX\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_mult_mtrx_test_1);
  tcase_add_test(tcase, matrix_mult_mtrx_test_2);
  tcase_add_test(tcase, matrix_mult_mtrx_test_3);
  tcase_add_test(tcase, matrix_mult_mtrx_test_4);
  tcase_add_test(tcase, matrix_mult_mtrx_test_5);

  suite_add_tcase(s, tcase);
  return s;
}
