#include "dense_matrix.h"
#include <stdexcept>

// обычная реализация умножения (i-j-k)
Matrix* DenseMatrix::mul(const Matrix& other) const {
    if (n_cols != other.rows()) {
        throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
    }

    size_t m = n_rows;
    size_t n = other.cols();
    size_t k = n_cols;

    DenseMatrix* result = new DenseMatrix(m, n);

    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            double sum = 0.0;
            for (size_t p = 0; p < k; p++) {
                sum += get(i, p) * other.get(p, j);
            }
            result->set(i, j, sum);
        }
    }

    return result;
}

// крутая реализация (i-k-j)
// Используем прямой доступ к данным через data[] вместо виртуальных get/set
Matrix* DenseMatrix::mulOptimized(const Matrix& other) const {
    if (n_cols != other.rows()) {
        throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
    }

    size_t m = n_rows;
    size_t n = other.cols();
    size_t k = n_cols;

    DenseMatrix* result = new DenseMatrix(m, n);

    // Приводим other к DenseMatrix для прямого доступа к данным
    const DenseMatrix* otherDense = dynamic_cast<const DenseMatrix*>(&other);
    if (!otherDense) {
        // Если other не DenseMatrix, используем виртуальные методы (fallback)
        for (size_t i = 0; i < m; i++) {
            for (size_t p = 0; p < k; p++) {
                double a_ip = get(i, p);
                for (size_t j = 0; j < n; j++) {
                    result->set(i, j, result->get(i, j) + a_ip * other.get(p, j));
                }
            }
        }
        return result;
    }

    // Прямой доступ к данным — без виртуальных вызовов и проверок границ
    const std::vector<double>& a_data = this->data;
    const std::vector<double>& b_data = otherDense->data;
    std::vector<double>& c_data = result->data;

    // Порядок i-k-j для кэш-дружественности
    for (size_t i = 0; i < m; i++) {
        size_t i_offset = i * n;      // смещение строки i в результате
        size_t ik_offset = i * k;     // смещение строки i в A
        for (size_t p = 0; p < k; p++) {
            double a_ip = a_data[ik_offset + p];
            size_t p_offset = p * n;  // смещение строки p в B
            for (size_t j = 0; j < n; j++) {
                c_data[i_offset + j] += a_ip * b_data[p_offset + j];
            }
        }
    }

    return result;
}

// В i-j-k мы читаем B по столбцам: B[0][0], B[1][0], B[2][0]...
// В i - k - j мы читаем B по строкам : B[0][0], B[0][1], B[0][2]... Это последовательное чтение(попадания в кэш). И ещё прямой доступ к data[]