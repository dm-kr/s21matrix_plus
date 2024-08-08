#ifndef S21_MATH_TEST_H_
#define S21_MATH_TEST_H_

#include <check.h>
#include <stdio.h>

#include "../s21_matrix.h"

Suite *suite_s21_create_matrix(void);
Suite *suite_s21_eq_matrix(void);
Suite *suite_s21_sum_matrix(void);
Suite *suite_s21_sub_matrix(void);
Suite *suite_s21_mult_number(void);
Suite *suite_s21_mult_matrix(void);
Suite *suite_s21_calc_complements(void);
Suite *suite_s21_transpose(void);
Suite *suite_s21_determinant(void);
Suite *suite_s21_inverse(void);

void run_tests(int *number_all, int *number_failed);
void run_testcase(Suite *testcase, int *number_all, int *number_failed);

#endif
