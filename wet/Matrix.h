//
// Created by areg6 on 24/05/2025.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "Utilities.h"
#include <cmath>

const char BAR = '|';

class Matrix {
    int* m_data;
    unsigned int m_rows;
    unsigned int m_columns;


    static bool checkSizes(const Matrix& matrix1, const Matrix& matrix2);
    static void swap(int& x, int& y);
    bool checkBounds(const unsigned int & i, const unsigned int & j) const;

public:
    // constructors and assignment
    Matrix() : m_data(nullptr), m_rows(0), m_columns(0) {}
    Matrix(unsigned int rows, unsigned int columns, int initiationNumber = 0);
    ~Matrix();
    Matrix(const Matrix& otherMatrix);
    Matrix& operator=(const Matrix& otherMatrix);

    // indexing and assignments per index
    int& operator()(unsigned int i, unsigned int j);
    int& operator()(unsigned int i, unsigned int j) const; // read-only

    // math
    Matrix& operator+=(const Matrix& otherMatrix);
    Matrix& operator-=(const Matrix& otherMatrix);
    Matrix& operator*=(const Matrix& otherMatrix);
    Matrix operator-() const;
    Matrix& operator*=(const int& scalar);

    // bool
    bool operator==(const Matrix& otherMatrix) const;
    bool operator!=(const Matrix& otherMatrix) const;

    // matrix manipulations
    Matrix rotateClockwise() const;

    Matrix rotateCounterClockwise() const;

    Matrix transpose() const;

    // static
    static double CalcFrobeniusNorm(const Matrix &matrix);

    friend std::ostream& operator<<(std::ostream& out, const Matrix& matrix); // return ostream& for chain ability

};

Matrix operator+(const Matrix& matrix1, const Matrix& matrix2);
Matrix operator-(const Matrix& matrix1, const Matrix& matrix2);
Matrix operator*(const Matrix& matrix1, const Matrix& matrix2);
Matrix operator*(const Matrix& matrix1, const int& scalar);
Matrix operator*(const int& scalar, const Matrix& matrix1);



#endif //MATRIX_H
