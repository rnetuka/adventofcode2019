//
// Created by rnetuka on 17.01.20.
//

#pragma once

#include <initializer_list>
#include <stdexcept>
#include <vector>


template <typename T>
class matrix;


template <typename T>
class matrix_row_iterator : public std::iterator<std::input_iterator_tag, T>
{
    const matrix<T>& matrix_;
    const int i;
    int j;

public:
    matrix_row_iterator(const matrix<T>& matrix, int i, int j = 1) : matrix_ { matrix }, i { i } {
        this->j = j;
    }

    T operator*() {
        return matrix_.at(i, j);
    }

    void operator++() {
        if (j > matrix_.width)
            throw std::logic_error("Iterator cannot be increased any further");
        j++;
    }

    bool operator==(const matrix_row_iterator<T>& other) {
        return i == other.i && j == other.j;
    }

    bool operator!=(const matrix_row_iterator<T>& other) {
        return !(*this == other);
    }

};


template <typename T>
class matrix_row {
public:
    const int width;

private:
    matrix<T>& matrix_;
    const int i;

public:
    matrix_row(matrix<T>& matrix, int i) : matrix_ { matrix }, i { i }, width { matrix.width } {

    }

    matrix_row_iterator<T> begin() const {
        return { matrix_, i };
    }

    matrix_row_iterator<T> end() const {
        return { matrix_, i , matrix_.width + 1 };
    }

    T& operator[](int j) {
        return matrix_.at(i, j);
    }

    void operator=(std::initializer_list<T> elements) {
        int j = 0;
        for (auto element : elements)
            matrix_.elements[i - 1][j++] = element;
    }

    void operator=(const std::vector<T>& elements) {
        int j = 0;
        for (auto element : elements)
            matrix_.elements[i - 1][j++] = element;
    }

};


template <typename T>
class matrix_const_row {
public:
    const int width;

private:
    const matrix<T>& matrix_;
    const int i;

public:
    matrix_const_row(const matrix<T>& matrix, int i) : matrix_ { matrix }, i { i }, width { matrix.width } {

    }

    matrix_row_iterator<T> begin() const {
        return { matrix_, i };
    }

    matrix_row_iterator<T> end() const {
        return { matrix_, i , matrix_.width + 1 };
    }

    T operator[](int j) const {
        return matrix_.at(i, j);
    }

};


template <typename T>
class matrix_column {
public:
    const int height;

private:
    matrix<T>& matrix_;
    const int j;

public:
    matrix_column(matrix<T>& matrix, int j) : matrix_ { matrix }, j { j }, height { matrix.height } {

    }

    T& operator[](int i) {
        return matrix_.at(i, j);
    }

    void operator=(std::initializer_list<T> elements) {
        int i = 0;
        for (auto element : elements)
            matrix_.elements[i++][j - 1] = element;
    }

    void operator=(const std::vector<T>& elements) {
        int i = 0;
        for (auto element : elements)
            matrix_.elements[i++][j - 1] = element;
    }
};


template <typename T>
class matrix final {
public:
    const int width;
    const int height;

private:
    T** elements;

public:
    matrix(int m, int n) : height { m }, width { n }
    {
        elements = new T*[height];
        for (int i = 0; i < height; i++) {
            elements[i] = new T[width];
            for (int j = 0; j < width; j++)
                elements[i][j] = 0;
        }
    }

    matrix(const matrix<T>& other) : matrix { other.width, other.height }
    {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                elements[i][j] = other.elements[i][j];
    }

    ~matrix() {
        if (elements) {
            for (int i = 0; i < height; i++)
                delete[] elements[i];

            delete[] elements;
        }
    }

    matrix_row<T> operator[](int i) {
        return row(i);
    }

    matrix_const_row<T> operator[](int i) const {
        return row(i);
    }

    matrix_row<T> row(int i) {
        if (i < 1 || i > height)
            throw std::out_of_range("Matrix index i must be between 1 and matrix height: " + std::to_string(i));

        return matrix_row { *this, i };
    }

    matrix_const_row<T> row(int i) const {
        if (i < 1 || i > height)
            throw std::out_of_range("Matrix index i must be between 1 and matrix height: " + std::to_string(i));

        return { *this, i };
    }

    matrix_column<T> column(int j) {
        if (j < 1 || j > width)
            throw std::out_of_range("Matrix index j must be between 1 and matrix width: " + std::to_string(j));

        return { *this, j };
    }

    T& at(int i, int j) {
        if (i < 1 || i > height)
            throw std::out_of_range("Matrix index i must be between 1 and matrix height: " + std::to_string(i));

        if (j < 1 || j > width)
            throw std::out_of_range("Matrix index j must be between 1 and matrix width: " + std::to_string(j));

        return elements[i - 1][j - 1];
    }

    const T& at(int i, int j) const {
        if (i < 1 || i > height)
            throw std::out_of_range("Matrix index i must be between 1 and matrix height: " + std::to_string(i));

        if (j < 1 || j > width)
            throw std::out_of_range("Matrix index j must be between 1 and matrix width: " + std::to_string(j));

        return elements[i - 1][j - 1];
    }

    matrix<T> operator*(matrix<T>& other) {
        if (width != other.height)
            throw std::logic_error("");

        matrix<T> result { height, other.width };

        for (int i = 0; i < result.height; i++)
            for (int j = 0; j < result.width; j++) {
                auto r = row(i + 1);
                auto c = other.column(j + 1);
                result.elements[i][j] = T();
                for (int k = 1; k <= r.width; k++)
                    result.elements[i][j] += (r[k] * c[k]);
            }
        return result;
    }

    matrix& operator=(matrix<T>&& other) noexcept {
        const_cast<int&>(height) = other.height;
        const_cast<int&>(width) = other.width;
        elements = other.elements;
        other.elements = nullptr;
        return *this;
    }

    friend class matrix_row<T>;
    friend class matrix_column<T>;

};