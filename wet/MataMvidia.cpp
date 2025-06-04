//
// Created by areg6 on 24/05/2025.
//

#include "MataMvidia.h"

MataMvidia::MataMvidia(const std::string &name, const std::string &producer, const Matrix *frames,
    unsigned int length) : m_length(length), m_frames(new Matrix[m_length]), m_name(name), m_producer(producer) {
    for (unsigned int i = 0; i < m_length; i++) {
        m_frames[i] = frames[i];
    }
}

MataMvidia::MataMvidia(const MataMvidia &otherMovie) {
    m_name = otherMovie.m_name;
    m_producer = otherMovie.m_producer;
    m_length = otherMovie.m_length;
    m_frames = new Matrix[m_length];
    for (unsigned int i = 0; i < otherMovie.m_length; i++) {
        m_frames[i] = otherMovie.m_frames[i];
    }
}

MataMvidia & MataMvidia::operator=(const MataMvidia &otherMovie) {
    if (this == &otherMovie) {
        return *this;
    }

    m_name = otherMovie.m_name;
    m_producer = otherMovie.m_producer;
    m_length = otherMovie.m_length;
    Matrix* newFrames = new Matrix[m_length];
    for (unsigned int i = 0; i < otherMovie.m_length; i++) {
        newFrames[i] = otherMovie.m_frames[i];
    }
    delete[] m_frames;
    m_frames = newFrames;

    return *this;

}

MataMvidia::~MataMvidia() {
    delete[] m_frames;
}

Matrix & MataMvidia::operator[](const unsigned int index) {
    if (index >= m_length) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return m_frames[index];
}

Matrix & MataMvidia::operator[](const unsigned int index) const {
    if (index >= m_length) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return m_frames[index];
}

MataMvidia & MataMvidia::operator+=(const MataMvidia &otherMovie) {
    const unsigned int newLength = m_length + otherMovie.m_length;
    Matrix* newFrames = new Matrix[newLength];

    for (unsigned int i = 0; i < newLength; i++) {
        if (i < m_length) {
            newFrames[i] = m_frames[i];
        }
        else {
            newFrames[i] = otherMovie.m_frames[i - m_length];
        }
    }

    m_length = newLength;

    delete[] m_frames;
    m_frames = newFrames;

    return *this;
}

MataMvidia & MataMvidia::operator+=(const Matrix &matrix) {
    const MataMvidia oneFrameMovie(EMPTY, EMPTY, &matrix, 1);
    (*this) += oneFrameMovie;

    return *this;
}

MataMvidia operator+(const MataMvidia &movie1, const MataMvidia &movie2) {
    MataMvidia movie3(movie1);
    return movie3 += movie2;
}

std::ostream & operator<<(std::ostream &out, const MataMvidia &movie) {
    out << "Movie Name: " << movie.m_name << std::endl;
    out << "Author: " << movie.m_producer << std::endl << std::endl;

    for (unsigned int i = 0; i < movie.m_length; i++) {
        out << "Frame " << i << ":" << std::endl;
        out << movie[i] << std::endl;
    }

    out << "-----End of Movie-----" << std::endl;

    return out;
}
