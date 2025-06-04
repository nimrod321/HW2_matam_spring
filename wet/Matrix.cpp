//
// Created by areg6 on 24/05/2025.
//

#include "Matrix.h"

Matrix::Matrix() : m_data(nullptr), m_rows(0), m_columns(0) {}

Matrix::Matrix(unsigned int rows, unsigned int columns, int initiationNumber) : m_rows(rows), m_columns(columns) {
    if (!rows || !columns) {
        m_rows = 0;
        m_columns = 0;
    }

    m_data = new int[columns * rows];
    for (unsigned int i = 0; i < m_columns * m_rows; i++) {
        m_data[i] = initiationNumber;
    }
}

Matrix::~Matrix() {
    delete[] m_data;
}

Matrix::Matrix(const Matrix &otherMatrix) {
    m_columns = otherMatrix.m_columns;
    m_rows = otherMatrix.m_rows;
    m_data = new int[otherMatrix.m_columns * otherMatrix.m_rows];
    for (unsigned int i = 0; i < m_columns * m_rows; i++) {
       m_data[i] = otherMatrix.m_data[i];
    }
}

Matrix & Matrix::operator=(const Matrix &otherMatrix) {
    if (this == &otherMatrix) {
        return *this;
    }
    int* dataCopy = new int[otherMatrix.m_columns * otherMatrix.m_rows];
    m_columns = otherMatrix.m_columns;
    m_rows = otherMatrix.m_rows;
    for (unsigned int i = 0; i < m_columns * m_rows; i++) {
        dataCopy[i] = otherMatrix.m_data[i];
    }
    delete[] m_data;
    m_data = dataCopy;

    return *this;
}

int & Matrix::operator()(const unsigned int i, const unsigned int j) {
    if (checkBounds(i, j)) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return m_data[i * m_columns + j];
}

int & Matrix::operator()(const unsigned int i, const unsigned int j) const {
    if (checkBounds(i, j)) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return m_data[i * m_columns + j];
}

Matrix & Matrix::operator+=(const Matrix &otherMatrix) {
    if (checkSizes(*this, otherMatrix)) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }

    for (unsigned int i = 0; i < m_columns * m_rows; ++i) {
        m_data[i] += otherMatrix.m_data[i];
    }

    return *this;
}

Matrix & Matrix::operator-=(const Matrix &otherMatrix) {
    return (*this += -otherMatrix);
}

Matrix & Matrix::operator*=(const Matrix &otherMatrix) {
    if (m_columns != otherMatrix.m_rows) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }

    Matrix resultMatrix(m_rows, otherMatrix.m_columns);
    for (unsigned int i = 0; i < m_rows; ++i) {
        for (unsigned int j = 0; j < otherMatrix.m_columns; ++j) {
            int sum = 0;
            for (unsigned int k = 0; k < m_columns; ++k) {
                sum += (*this)(i, k) * otherMatrix(k, j);
            }
            resultMatrix(i,j) = sum;
        }
    }

    *this = resultMatrix;
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix negativeMatrix(*this);
    negativeMatrix *= -1;

    return negativeMatrix;
}

Matrix & Matrix::operator*=(const int &scalar) {
    for (unsigned int i = 0; i < m_columns * m_rows; ++i) {
        m_data[i] *= scalar;
    }

    return *this;
}

bool Matrix::operator==(const Matrix &otherMatrix) const {
    if (checkSizes(*this, otherMatrix)) {
        return false;
    }

    for (unsigned int i = 0; i < m_columns * m_rows; ++i) {
        if (m_data[i] != otherMatrix.m_data[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix &otherMatrix) const {
    return !(*this == otherMatrix);
}

Matrix Matrix::rotateClockwise() const {
    Matrix rotatedMatrix = *this;
    rotatedMatrix = rotatedMatrix.transpose();

    // mirroring
    for (unsigned int i = 0; i < rotatedMatrix.m_rows; ++i) {
        for (unsigned int j = 0, k = rotatedMatrix.m_columns - 1; j < k; j++, k--) {
            swap(rotatedMatrix(i, j), rotatedMatrix(i, k));
        }
    }

    return rotatedMatrix;

}

Matrix Matrix::rotateCounterClockwise() const {
    return this->rotateClockwise().rotateClockwise().rotateClockwise();
}

Matrix Matrix::transpose() const {
    Matrix transposedMatrix(m_columns, m_rows);
    for (unsigned int i = 0; i < m_rows; ++i) {
        for (unsigned int j = 0; j < m_columns; ++j) {
            transposedMatrix(j, i) = (*this)(i, j);
        }
    }
    return transposedMatrix;

}

double Matrix::CalcFrobeniusNorm(const Matrix &matrix) {
    double sum = 0;
    for (unsigned int i = 0; i < matrix.m_columns * matrix.m_rows; ++i) {
        sum += matrix.m_data[i] * matrix.m_data[i];
    }
    return std::sqrt(sum);
}

std::ostream & operator<<(std::ostream& out, const Matrix &matrix) {
    if (matrix.m_rows && matrix.m_columns) {
        for (unsigned int i = 0; i < matrix.m_rows; ++i) {
            out << BAR;
            for (unsigned int j = 0; j < matrix.m_columns; ++j) {
                out << matrix(i, j) << BAR;
            }
            out << std::endl;
        }
    }

    return out;
}

Matrix operator+(const Matrix &matrix1, const Matrix &matrix2) {
    Matrix matrix3(matrix1);
    return matrix3 += matrix2;
}

Matrix operator-(const Matrix &matrix1, const Matrix &matrix2) {
    Matrix matrix3(matrix1);
    return (matrix3 -= matrix2);
}

Matrix operator*(const Matrix &matrix1, const Matrix &matrix2) {
    Matrix matrix3(matrix1);
    return matrix3 *= matrix2;
}

Matrix operator*(const Matrix &matrix1, const int &scalar) {
    Matrix matrix2(matrix1);
    return matrix2 *= scalar;
}

Matrix operator*(const int &scalar, const Matrix &matrix1) {
    return matrix1 * scalar;
}

// ---------------------- static functions ---------------------- //
bool Matrix::checkSizes(const Matrix &matrix1, const Matrix &matrix2) {
    return matrix1.m_columns != matrix2.m_columns || matrix1.m_rows != matrix2.m_rows;
}

void Matrix::swap(int &x, int &y) {
    const int temp = x;
    x = y;
    y = temp;
}

bool Matrix::checkBounds(const unsigned int & i, const unsigned int & j) const {
    if (i >= m_rows || j >= m_columns) {
        return true;
    }
    return false;
}
