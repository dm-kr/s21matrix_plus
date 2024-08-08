#include "s21_test.h"

START_TEST(matrix_inverse_test_1) {
  double array[1][1] = {{2}};
  int row = 1;
  int col = 1;
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t res_check = {0};
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  res_check.matrix[0][0] = 1.0 / 2.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&res_check, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_inverse_test_2) {
  double array[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_inverse_test_3) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  double array_res[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};
  int row = 3;
  int col = 3;
  matrix_t A = {0};
  matrix_t res_check = {0};
  matrix_t result = {0};
  s21_create_matrix(row, col, &A);
  s21_create_matrix(row, col, &res_check);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
      res_check.matrix[i][j] = array_res[i][j];
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&res_check, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_check);
}
END_TEST

START_TEST(matrix_inverse_test_4) {
  double array[3][2] = {{1, 2}, {0, 4}, {5, 2}};
  int row = 3;
  int col = 2;
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_inverse_test_5) {
  matrix_t A = {0};
  matrix_t result = {0};
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(matrix_inverse_test_6) {
  double array[3][3] = {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}};
  int row = 3;
  int col = 2;
  matrix_t A = {0};
  s21_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_inverse_test_7) {
  double array[1][1] = {{0}};
  int row = 1;
  int col = 1;
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(row, col, &A);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      A.matrix[i][j] = array[i][j];
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_s21_inverse(void) {
  Suite *s = suite_create("\033[42mS21_INVERSE\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_inverse_test_1);
  tcase_add_test(tcase, matrix_inverse_test_2);
  tcase_add_test(tcase, matrix_inverse_test_3);
  tcase_add_test(tcase, matrix_inverse_test_4);
  tcase_add_test(tcase, matrix_inverse_test_5);
  tcase_add_test(tcase, matrix_inverse_test_6);
  tcase_add_test(tcase, matrix_inverse_test_7);

  suite_add_tcase(s, tcase);
  return s;
}
