//
// Created by areg6 on 24/05/2025.
//

#ifndef MATAMVIDIA_H
#define MATAMVIDIA_H

#include "Matrix.h"
#include <string>

const std::string EMPTY;

class MataMvidia {
    unsigned int m_length;
    Matrix* m_frames;
    std::string m_name;
    std::string m_producer;

public:
    // constructors
    ~MataMvidia();
    MataMvidia(const std::string& name, const std::string& producer, const Matrix* frames, unsigned int length);
    MataMvidia(const MataMvidia& otherMovie);

    // assignment operator
    MataMvidia& operator=(const MataMvidia& otherMovie);

    // operators
    Matrix& operator[](unsigned int index);
    Matrix& operator[](unsigned int index) const; // read-only

    // appending frames
    MataMvidia& operator+=(const MataMvidia& otherMovie);
    MataMvidia& operator+=(const Matrix& matrix);

    // print operator
    friend std::ostream& operator<<(std::ostream& out, const MataMvidia& movie);

};

// appending movies (symmetry)

MataMvidia operator+(const MataMvidia& movie1, const MataMvidia& movie2);


#endif //MATAMVIDIA_H
