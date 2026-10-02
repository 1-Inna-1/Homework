#pragma once
#include "matrix.h"
#include <vector>
#include <stdexcept>

class DenseMatrix : public Matrix {
private:
    std::vector<double> data;  // плоский вектор (row-major)
    size_t n_rows;
    size_t n_cols;

    // чтобы найти элемент в строке row и столбце col
    size_t index(size_t row, size_t col) const {
        return row * n_cols + col;
    }

public:
    // создание матрицы, заполненной нулями
    DenseMatrix(size_t rows, size_t cols)
        : n_rows(rows), n_cols(cols), data(rows* cols, 0.0) {
    }

    // Конструктор из вектора векторов (для удобства в тестах)
    DenseMatrix(const std::vector<std::vector<double>>& init) {
        n_rows = init.size();
        n_cols = init[0].size();
        data.resize(n_rows * n_cols);
        for (size_t i = 0; i < n_rows; i++) {
            for (size_t j = 0; j < n_cols; j++) {
                data[index(i, j)] = init[i][j];
            }
        }
    }

    // Реализация методов интерфейса
    double get(size_t row, size_t col) const override {
        if (row >= n_rows || col >= n_cols) {
            throw std::out_of_range("Index out of range");
        }
        return data[index(row, col)];
    }

    void set(size_t row, size_t col, double value) override {
        if (row >= n_rows || col >= n_cols) {
            throw std::out_of_range("Index out of range");
        }
        data[index(row, col)] = value;
    }

    size_t rows() const override { return n_rows; }
    size_t cols() const override { return n_cols; }

    // Умножение матриц (i-j-k)
    Matrix* mul(const Matrix& other) const override;

    // Оптимизированное умножение (i-k-j)
    Matrix* mulOptimized(const Matrix& other) const;
};