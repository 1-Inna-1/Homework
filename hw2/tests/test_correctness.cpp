#include <iostream>
#include <vector>
#include <cmath>
#include <windows.h>
#include "../dense_matrix.h"

// Проверка правильности умножения, проверка одинаково размера у матриц, проходит по каждому элементу обеих матриц и сравнивает с 1е-9
bool matricesEqual(const Matrix& a, const Matrix& b, double tolerance = 1e-9) {
    if (a.rows() != b.rows() || a.cols() != b.cols()) return false;

    for (size_t i = 0; i < a.rows(); i++) {
        for (size_t j = 0; j < a.cols(); j++) {
            if (std::abs(a.get(i, j) - b.get(i, j)) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    SetConsoleOutputCP(65001);

    int passed = 0;
    int total = 0;

    {
        total++;
        std::cout << "Тест 1: Умножение на единичную матрицу" << std::endl;

        DenseMatrix A({ { 1, 2 },{ 3, 4 } });
        DenseMatrix I({ { 1, 0 },{ 0, 1 } });

        Matrix* result = A.mul(I);
        if (matricesEqual(A, *result)) {
            std::cout << "  [OK] A * I = A" << std::endl;
            passed++;
        }
        else {
            std::cout << "  [FAIL] A * I != A" << std::endl;
        }
        delete result;
    }

    {
        total++;
        std::cout << "Тест 2: Умножение на нулевую матрицу" << std::endl;

        DenseMatrix A({ { 1, 2 },{ 3, 4 } });
        DenseMatrix Z({ { 0, 0 },{ 0, 0 } });
        DenseMatrix expected({ { 0, 0 },{ 0, 0 } });

        Matrix* result = A.mul(Z);
        if (matricesEqual(expected, *result)) {
            std::cout << "  [OK] A * 0 = 0" << std::endl;
            passed++;
        }
        else {
            std::cout << "  [FAIL] A * 0 != 0" << std::endl;
        }
        delete result;
    }

    {
        total++;
        std::cout << "Тест 3: Ручной пример 2×2" << std::endl;

        DenseMatrix A({ { 1, 2 },{ 3, 4 } });
        DenseMatrix B({ { 5, 6 },{ 7, 8 } });
        DenseMatrix expected({ { 19, 22 },{ 43, 50 } });

        Matrix* result = A.mul(B);
        if (matricesEqual(expected, *result)) {
            std::cout << "  [OK] 2×2 умножение верно" << std::endl;
            passed++;
        }
        else {
            std::cout << "  [FAIL] 2×2 умножение неверно" << std::endl;
        }
        delete result;
    }

    {
        total++;
        std::cout << "Тест 4: Неквадратные матрицы (2×3 × 3×2)" << std::endl;

        DenseMatrix A({ { 1, 2, 3 },{ 4, 5, 6 } });
        DenseMatrix B({ { 7, 8 },{ 9, 10 },{ 11, 12 } });
        DenseMatrix expected({ { 58, 64 },{ 139, 154 } });

        Matrix* result = A.mul(B);
        if (matricesEqual(expected, *result)) {
            std::cout << "  [OK] 2×3 × 3×2 = 2×2 верно" << std::endl;
            passed++;
        }
        else {
            std::cout << "  [FAIL] 2×3 × 3×2 неверно" << std::endl;
        }
        delete result;
    }

    {
        total++;
        std::cout << "Тест 5: Несовместимые размеры" << std::endl;

        DenseMatrix A({ { 1, 2 },{ 3, 4 } });
        DenseMatrix B({ { 1, 2, 3 } });  // 1×3, несовместимо с 2×2

        try {
            Matrix* result = A.mul(B);
            delete result;
            std::cout << "  [FAIL] Исключение не выброшено" << std::endl;
        }
        catch (const std::invalid_argument& e) {
            std::cout << "  [OK] Исключение выброшено: " << e.what() << std::endl;
            passed++;
        }
    }

    {
        total++;
        std::cout << "Тест 6: Наивная vs оптимизированная" << std::endl;

        DenseMatrix A({ { 1, 2 },{ 3, 4 } });
        DenseMatrix B({ { 5, 6 },{ 7, 8 } });

        Matrix* naive = A.mul(B);
        Matrix* optimized = A.mulOptimized(B);

        if (matricesEqual(*naive, *optimized)) {
            std::cout << "  [OK] Результаты совпадают" << std::endl;
            passed++;
        }
        else {
            std::cout << "  [FAIL] Результаты не совпадают" << std::endl;
        }
        delete naive;
        delete optimized;
    }

    std::cout << "\n=== Результат: " << passed << " из " << total << " тестов пройдено ===" << std::endl;

    return (passed == total) ? 0 : 1;
}