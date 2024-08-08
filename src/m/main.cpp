#include <iostream>

#include "../s21_matrix_oop.h"

int main() {
  S21Matrix A;
  std::cout << A.getRows() << "," << A.getCols() << std::endl;
  S21Matrix B(2, 3);
  std::cout << B.getRows() << "," << B.getCols() << std::endl;

  return 0;
}