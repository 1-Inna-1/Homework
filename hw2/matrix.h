#pragma once
#include <vector>
#include <stdexcept>

class Matrix {
public:
    virtual ~Matrix() = default;

    // Получить элемент по индексу
    virtual double get(size_t row, size_t col) const = 0;

    // Установить элемент
    virtual void set(size_t row, size_t col, double value) = 0;

    // Получить количество строк
    virtual size_t rows() const = 0;

    // Получить количество столбцов
    virtual size_t cols() const = 0;

    // Умножение матриц
    virtual Matrix* mul(const Matrix& other) const = 0;
};