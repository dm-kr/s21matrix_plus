#include "s21_test.h"

START_TEST(matrix_create_test_1) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_create_test_2) {
  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(matrix_create_test_3) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(3, 0, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(matrix_create_test_4) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(0, 3, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(matrix_create_test_5) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(matrix_create_test_6) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(
                       (unsigned int)0b11111111111111111111111111111111, 1, &A),
                   INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

Suite *suite_s21_create_matrix(void) {
  Suite *s = suite_create("\033[42mS21_CREATE_MATRIX\033[0m");
  TCase *tcase = tcase_create("create_tc");

  tcase_add_test(tcase, matrix_create_test_1);
  tcase_add_test(tcase, matrix_create_test_2);
  tcase_add_test(tcase, matrix_create_test_3);
  tcase_add_test(tcase, matrix_create_test_4);
  tcase_add_test(tcase, matrix_create_test_5);
  tcase_add_test(tcase, matrix_create_test_6);

  suite_add_tcase(s, tcase);
  return s;
}
