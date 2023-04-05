#pragma once
#include <iostream>
#include <vector>
#include "MatrixTerm.h"
#include "myExceptions.h"

template<class T, const T Zero = T()>
class SparseMatrix
{
public:
    /* Constructors */

    /**
     * @brief Create a{row}* {col} sparse matrix.
     * @exception illegalParameterValue if {row} or {col} is <= 0.
    */
    SparseMatrix(int row, int col);

    /* Element Access */

    /**
     * @brief Get the value of the element at({row}, {col}) (non-const version).
     * @exception matrixIndexOutOfBounds if {row} or {col} is out of range.
    */
    T& get(int row, int col);
    /**
     * @brief Get the value of the element at ({row}, {col}) (const version).
     * @exception matrixIndexOutOfBounds if {row} or {col} is out of range.
    */
    const T& get(int row, int col) const;

    /* Capacity */

    // @brief Get the number of rows in the matrix.
    int rows() { return _rows; }
    // @brief Get the number of columns in the matrix.
    int cols() { return _cols; }
    // @brief Get the total number of elements in the matrix.
    int size() { return _rows * _cols; }
    // @brief Get the total number of non-zero elements in the matrix.
    int non_zero_size() { return (int)_terms.size(); }

    /* Modifiers */

    /**
     * @brief Set the value of the element at ({row}, {col}) as {val}.
     * @exception matrixIndexOutOfBounds if {row} or {col} is out of range.
    */
    void set(int row, int col, const T& val);
    //@brief Transpose the matrix in a fast but complicated way.
    void transpose();
    //@brief Transpose the matrix in a simple but slow way.
    void transpose_alt();
    /**
     * @brief Add two matrices together.
     * @exception matrixSizeMismatch if the shapes of these two matrices are different.
    */
    SparseMatrix<T> operator+(const SparseMatrix<T>& mat);
    /**
     * @brief Subtract one matrix from another.
     * @exception matrixSizeMismatch if the shapes of these two matrices are different.
    */
    SparseMatrix<T> operator-(const SparseMatrix<T>& mat);
    /**
     * @brief Multiply two matrices together.
     * @exception matrixSizeMismatch if these matrices are not multipliable.
    */
    SparseMatrix<T> operator*(const SparseMatrix<T>& mat);

    /* Output */

    /** @brief Output the sparse matrix.
     *     (row, col, value)
    */
    void outputSparse(std::ostream& out = std::cout) const;
    /**
     * @brief Output the full matrix.
     *     [e_00 e_01 ... e_0n]
     *     [e_10 e_11 ... e_1n]
     *     [...  ...  ... ... ]
     *     [e_m0 e_m1 ... e_mn]
    */
    void outputFull(std::ostream& out = std::cout) const;

protected:
    std::vector<MatrixTerm<T>> _terms;  // Non-zero elements.
    int _rows;  // Number of rows in the matrix.
    int _cols;  // Number of cols in the matrix.
};

template< class T, const T Zero>
SparseMatrix<T, Zero>::SparseMatrix(int row, int col)
    :_terms(0) {  // Initialize {_terms} by setting its size to 0.
    // Throw an exception if {row} or {col} is illegal:
    if (row <= 0 || col <= 0) {
        throw illegalParameterValue("Row and col must be > 0!");
    }
    _rows = row;
    _cols = col;
}

template< class T, const T Zero>
T& SparseMatrix<T, Zero>::get(int row, int col) {
    auto c_this = const_cast<SparseMatrix<T> const*>(this);
    return const_cast<T&>(c_this->get(row, col));
}

template< class T, const T Zero>
const T& SparseMatrix<T, Zero>::get(int row, int col) const {
    // Throw an exception if {row} or {col} is out of range:
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
        throw matrixIndexOutOfBounds();
    }

    // Check if mat[{row}][{col}] exists in {_terms} (i.e. mat[{row}][{col}] is a non-zero element):
    int index = 0;
    for (; index < _terms.size() &&
        (_terms[index].row < row || _terms[index].row == row && _terms[index].col < col); index++);

    // Return its value if the element is found in {_terms}:
    if (index < _terms.size() && _terms[index].row == row && _terms[index].col == col) {
        return _terms[index].val;
    }
    // Otherwise, return Zero:
    return Zero;
}

template< class T, const T Zero>
void SparseMatrix<T, Zero>::set(int row, int col, const T& val) {
    // Throw an exception if {row} or {col} is out of range:
    if (row < 0 || row >= _rows || col < 0 || col >= _cols) {
        throw matrixIndexOutOfBounds();
    }

    // Check if mat[{row}][{col}] exists in {_terms} (i.e. mat[{row}][{col}] is a non-zero element):
    int index = 0;
    for (; index < _terms.size() &&
        (_terms[index].row < row || _terms[index].row == row && _terms[index].col < col); index++);

    // If mat[{row}][{col}] ¡Ù Zero,
    //     erase it from {_terms} if {val} = Zero,
    //     otherwise, set its value to {val}.
    // Otherwise,
    //     insert the element into {_terms} if {val} ¡Ù Zero,
    //     otherwise, do nothing.
    if (index < _terms.size() && _terms[index].row == row && _terms[index].col == col) {
        if (val == Zero) {
            _terms.erase(_terms.begin() + index);
        } else {
            _terms[index].val = val;
        }
    } else {
        if (val != Zero) {
            _terms.insert(_terms.begin() + index, MatrixTerm<T>{ row, col, val });
        }
    }
}

template< class T, const T Zero>
void SparseMatrix<T, Zero>::transpose() {
    // Get the number of elements in every column:
    std::vector<int> colSize(_cols, 0);
    for (const auto& element : _terms) {
        colSize[element.col]++;
    }

    // Find the index of the first element in every row in the transposed matrix,
    // which will be placed in {newTerms} defined below:
    std::vector<int> rowNext(_cols);  // Records where the next element in every row will be placed in {newTerms}.
    rowNext[0] = 0;
    for (int i = 1; i < _cols; i++) {
        // Index of the first element in {i}th row (transposed matrix)
        // = Index of the first element in {i-1}th row (transposed matrix)
        //   + the number of elements in {i-1}th column (original matrix).
        rowNext[i] = rowNext[i - 1] + colSize[i - 1];
    }

    // Sort {_terms} by column.
    std::vector<MatrixTerm<T>> newTerms(_terms.size());  // {_terms} of the transposed matrix.
    for (const auto& element : _terms) {
        // Get the index of the current element,
        // and then update the index of the next element in the {element.col}th row:
        int index = rowNext[element.col]++;
        // Swap {col} and {row}
        newTerms[index] = MatrixTerm<T>{ element.col, element.row, element.val };
    }

    // Swap the number of rows and columns, and relace {_terms} with {newTerms}:
    std::swap(_rows, _cols);
    _terms = std::move(newTerms);
}

template< class T, const T Zero>
void SparseMatrix<T, Zero>::transpose_alt() {
    std::vector<MatrixTerm<T>> newTerms(_terms.size());  // {_terms} of the transposed matrix.
    // Sort {_terms} by column:
    int index = 0;
    // Traverse {_terms} for {_cols} times.
    for (int col = 0; col < _cols; col++) {
        for (int j = 0; j < _terms.size(); j++) {
            // Place the element in {newTerms} if its column matches with the current {col}.
            if (_terms[j].col == col) {
                newTerms[index++] = MatrixTerm<T>{ _terms[j].col, _terms[j].row, _terms[j].val };
            }
        }
    }
    // Swap the number of rows and columns, and relace {_terms} with {newTerms}:
    std::swap(_rows, _cols);
    _terms = std::move(newTerms);
}

template< class T, const T Zero>
SparseMatrix<T> SparseMatrix<T, Zero>::operator+(const SparseMatrix<T>& mat) {
    // Throw an exception if these matrices are not addable.
    if (_rows != mat._rows || _cols != mat._cols) {
        throw matrixSizeMismatch();
    }
    SparseMatrix<T> resMat(_rows, _cols);  // Result of (*this + mat).
    // Iterators for traversing {*this} and {mat}
    auto iter_this = _terms.begin();
    auto iter_mat = mat._terms.begin();

    while (iter_this != _terms.end() && iter_mat != mat._terms.end()) {
        // Get the positions of elements that the iterators above are pointing to.
        int pos_this = iter_this->row * _cols + iter_this->col;
        int pos_mat = iter_mat->row * _cols + iter_mat->col;

        if (pos_this == pos_mat) {  // Both matrices have non-zero elements at the corresponding position
            T element = iter_this->val + iter_mat->val;
            if (element != Zero) {
                resMat._terms.push_back(MatrixTerm<T>{iter_this->row, iter_this->col, element});
            }
            iter_this++;
            iter_mat++;
        } else if (pos_this < pos_mat) {  // Element at the same position of {iter_this} in {mat} = Zero
            resMat._terms.push_back(*(iter_this++));
        } else {  // Element at the same position of {iter_mat} in {*this} = Zero
            resMat._terms.push_back(*(iter_mat++));
        }
    }
    // Place the rest of elements in {*this} or {mat} at the back of {resMat._terms}:
    for (; iter_this != _terms.end(); iter_this++) { resMat._terms.push_back(*iter_this); }
    for (; iter_mat != mat._terms.end(); iter_mat++) { resMat._terms.push_back(*iter_mat); }
    return resMat;
}

template< class T, const T Zero>
SparseMatrix<T> SparseMatrix<T, Zero>::operator-(const SparseMatrix<T>& mat) {
    // Throw an exception if these matrices are not subtractable.
    if (_rows != mat._rows || _cols != mat._cols) {
        throw matrixSizeMismatch();
    }
    SparseMatrix<T> resMat(_rows, _cols);  // Result of (*this - mat).
    // Iterators for traversing {*this} and {mat}
    auto iter_this = _terms.begin();
    auto iter_mat = mat._terms.begin();
    while (iter_this != _terms.end() && iter_mat != mat._terms.end()) {
        // Get the positions of elements that the iterators above are pointing to.
        int index_this = iter_this->row * _cols + iter_this->col;
        int index_mat = iter_mat->row * _cols + iter_mat->col;

        if (index_this == index_mat) {  // Both matrices have non-zero elements at the corresponding position
            T element = iter_this->val - iter_mat->val;
            if (element != Zero) {
                resMat._terms.push_back(MatrixTerm<T>{iter_this->row, iter_this->col, element});
            }
            iter_this++;
            iter_mat++;
        } else if (index_this < index_mat) {  // Element at the same position of {iter_this} in {mat} = Zero
            resMat._terms.push_back(*(iter_this++));
        } else {  // Element at the same position of {iter_mat} in {*this} = Zero
            resMat._terms.push_back(MatrixTerm<T>{iter_mat->row, iter_mat->col, -iter_mat->val});
            iter_mat++;
        }
    }
    // Place the rest of elements in {*this} at the back of {resMat._terms}:
    for (; iter_this != _terms.end(); iter_this++) {
        resMat._terms.push_back(*iter_this);
    }
    // Place at the back of {resMat._terms} the rest of elements in {*this},
    // but their values take the opposite number:
    for (; iter_mat != mat._terms.end(); iter_mat++) {
        resMat._terms.push_back(MatrixTerm<T>{iter_mat->row, iter_mat->col, -iter_mat->val});
    }
    return resMat;
}

template< class T, const T Zero>
void SparseMatrix<T, Zero>::outputSparse(std::ostream& out) const {
    for (const auto& term : _terms) {
        out << "(" << term.row << ", " << term.col << ", " << term.val << ")" << std::endl;
    }
    out << std::endl;
}

template< class T, const T Zero>
void SparseMatrix<T, Zero>::outputFull(std::ostream& out) const {
    std::vector<T> rowVec(_cols, Zero);
    auto iter = _terms.begin();
    for (int i = 0; i < _rows; i++) {
        out << "[";
        for (int j = 0; j < _cols; j++) {
            if (iter != _terms.end() && iter->row == i && iter->col == j) {
                out << (iter++)->val;
            } else {
                out << Zero;
            }
            out << (j < _cols - 1 ? " " : "]");
        }
        out << std::endl;
    }
}

/* Non-member functions */

// @brief Output the full matrix.
template<class T>
std::ostream& operator<<(std::ostream& out, const SparseMatrix<T>& mat) {
    mat.outputFull(out);
    return out;
}
