#include<iostream>
#include"SparseMatrix.h"

void sparseMatrixTest() {
    SparseMatrix<int> mat1(4, 6);
    mat1.set(1, 1, -4);
    mat1.set(1, 2, 9);
    mat1.set(1, 5, 10);
    mat1.set(1, 4, 9);
    mat1.set(3, 1, -8);
    mat1.set(3, 3, 1);
    std::cout << mat1 << std::endl;

    SparseMatrix<int> mat2(4, 6);
    mat2.set(0, 1, 4);
    mat2.set(1, 1, 1);
    mat2.set(1, 2, 3);
    mat2.set(2, 4, 3);
    mat2.set(3, 3, -5);
    mat2.set(3, 3, -1);
    std::cout << mat2 << std::endl;

    SparseMatrix<int> mat3 = mat1 - mat2;
    std::cout << mat3 << std::endl;
    mat3.outputSparse();

    std::cout << mat3.get(0, 1) << std::endl;
    mat3.get(0, 1) = 12;
    std::cout << mat3 << std::endl;
}