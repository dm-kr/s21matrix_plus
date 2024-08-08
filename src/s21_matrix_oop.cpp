#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  int rows = 3;
  int cols = 3;
  this->rows_ = rows;
  this->cols_ = cols;
  allocate_matrix(rows, cols, &this->matrix_);
}

S21Matrix::S21Matrix(int rows, int cols) {
  check_size_errors(rows, cols);
  this->rows_ = rows;
  this->cols_ = cols;
  allocate_matrix(rows, cols, &this->matrix_);
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  // TODO check if matrix is incorrect
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  allocate_matrix(this->rows_, this->cols_, &this->matrix_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      other.matrix_[i][j] = this->matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.~S21Matrix();
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < this->rows_; i++) {
    free(this->matrix_[i]);
  }
  free(this->matrix_);
}

int S21Matrix::getRows() const { return this->rows_; }
int S21Matrix::getCols() const { return this->cols_; }

void S21Matrix::setRows(int rows) {
  if (rows > 0) {
    this->rows_ = rows;
  } else {
    throw std::invalid_argument("Number of rows must be greater than zero.");
  }
}

void S21Matrix::setCols(int cols) {
  if (cols > 0) {
    cols_ = cols;
  } else {
    throw std::invalid_argument("Number of columns must be greater than zero.");
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) {}

void check_size_errors(int rows, int cols) {
  if (rows < 1) {
    throw std::invalid_argument("Wrong number of rows!");
  }
  if (cols < 1) {
    throw std::invalid_argument("Wrong number of cols!");
  }
}

void allocate_matrix(int rows, int cols, double ***matrix) {
  *matrix = (double **)calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    (*matrix)[i] = (double *)calloc(cols, sizeof(double));
  }
}
