#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <windows.h>
#include "../dense_matrix.h"

// Генерация случайной матрицы
DenseMatrix randomMatrix(size_t rows, size_t cols) {
    DenseMatrix m(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            m.set(i, j, static_cast<double>(rand() % 100) / 10.0);
        }
    }
    return m;
}

// Замер времени умножения
double measureTime(const DenseMatrix& A, const DenseMatrix& B, bool optimized) {
    auto start = std::chrono::high_resolution_clock::now();
    Matrix* result = optimized ? A.mulOptimized(B) : A.mul(B);
    auto end = std::chrono::high_resolution_clock::now();
    delete result;
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    SetConsoleOutputCP(65001);
    srand(42);

    std::cout << "=== Бенчмарк умножения матриц ===" << std::endl;
    std::cout << std::left << std::setw(10) << "Размер "
        << std::setw(15) << "Наивная (мс)"
        << std::setw(15) << "Оптимиз. (мс)"
        << std::setw(15) << "Ускорение" << std::endl;
    std::cout << std::string(55, '-') << std::endl;

    for (int size : {100, 200, 500, 1000}) {
        DenseMatrix A = randomMatrix(size, size);
        DenseMatrix B = randomMatrix(size, size);

        double naiveTime = measureTime(A, B, false);
        double optTime = measureTime(A, B, true);
        double speedup = naiveTime / optTime;

        std::cout << std::left << std::setw(10) << size
            << std::fixed << std::setprecision(2)
            << std::setw(15) << naiveTime
            << std::setw(15) << optTime
            << std::setw(15) << speedup << std::endl;
    }

    return 0;
}