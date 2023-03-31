#pragma once
#include <vector>
#include "MatrixTerm.h"
#include "myExceptions.h"

template<class T>
class SparseMatrix
{
public:
    // constructors
    SparseMatrix();
    SparseMatrix(const SparseMatrix<T>& mat);
    SparseMatrix<T>& operator=(const SparseMatrix<T>&);

    int rows() { return theRows; }
    int cols() { return theCols; }
    int size() { return terms.size(); }
    T& get(int row, int col); // non-const version
    const T& get(int row, int col) const; // const version
    void set(int row, int col, const T& val);
    SparseMatrix<T>& operator+(const SparseMatrix<T>& mat);
    const SparseMatrix<T>& operator+(const SparseMatrix<T>& mat) const;
protected:
    // data members
    std::vector<MatrixTerms<T>> terms; // non-zero elements
    int theRows;
    int theCols;
};

template<class T>
T& SparseMatrix<T>::get(int row, int col) { // non-const version
    // If row or col is out of bounds, throw exception:
    if (row < 0 || row >= theRows || col < 0 || col >= theCols) {
        throw matrixIndexOutOfBounds();
    }
    // Check if mat[row][col] exists in terms (i.e. non-zero elements):
    int index = 0;
    for (; index < terms.size() && (terms[index].row < row || terms[index].row == row && terms[index].col < col); index++);
    if (index == terms.size() && terms[index].row == row && terms[index].col == col) {
        return terms[index].val; // Non-zero elements.
    }
    return 0;
}

template<class T>
const T& SparseMatrix<T>::get(int row, int col) const { // const version
    // If row or col is out of bounds, throw exception:
    if (row < 0 || row >= theRows || col < 0 || col >= theCols) {
        throw matrixIndexOutOfBounds();
    }
    // Check if mat[row][col] exists in terms (i.e. non-zero elements):
    int index = 0;
    for (; index < terms.size() && (terms[index].row < row || terms[index].row == row && terms[index].col < col); index++);
    if (index == terms.size() && terms[index].row == row && terms[index].col == col) {
        return terms[index].val; // Non-zero elements.
    }
    return 0;
}

template<class T>
void SparseMatrix<T>::set(int row, int col, const T& val) {
    // If row or col is out of bounds, throw exception:
    if (row < 0 || row >= theRows || col < 0 || col >= theCols) {
        throw matrixIndexOutOfBounds();
    }
    int index = 0;
    for (; index < terms.size() && (terms[index].row < row || terms[index].row == row && terms[index].col < col); index++);
    // If mat[row][col] ¡Ù 0
    if (index == terms.size() && terms[index].row == row && terms[index].col == col) {
        // If val = 0, remove terms[index]. Otherwise,  val
        if (val == 0) {
            std::copy(terms.begin() + index + 1, terms.end(), terms.begin() + index);
            terms.pop_back();
        } else {
            terms[index].val = val
        }
    } else {
        if (val != 0) {
            terms
        }
    }
}

template<class T>
SparseMatrix<T>& SparseMatrix<T>::operator+(const SparseMatrix<T>& mat) {
    for (int i = 0; i < )
}
