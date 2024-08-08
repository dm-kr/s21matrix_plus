#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdexcept>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

#define ADD 1
#define SUB -1

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int getRows() const;
  int getCols() const;

  void setRows(int rows);
  void setCols(int cols);

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
};

// UTILS

void check_size_errors(int rows, int cols);
void allocate_matrix(int rows, int cols, double ***matrix);

// TASK

int s21_create_matrix(int rows, int columns, S21Matrix *result);
void s21_remove_matrix(S21Matrix *A);

int s21_eq_matrix(S21Matrix *A, S21Matrix *B);

int s21_sum_matrix(S21Matrix *A, S21Matrix *B, S21Matrix *result);
int s21_sub_matrix(S21Matrix *A, S21Matrix *B, S21Matrix *result);
int s21_mult_number(S21Matrix *A, double number, S21Matrix *result);
int s21_mult_matrix(S21Matrix *A, S21Matrix *B, S21Matrix *result);

int s21_transpose(S21Matrix *A, S21Matrix *result);
int s21_calc_complements(S21Matrix *A, S21Matrix *result);
int s21_determinant(S21Matrix *A, double *result);
int s21_inverse_matrix(S21Matrix *A, S21Matrix *result);

#endif