#include <iostream>
#include <vector>
#include <chrono>           
#include <iomanip>        
#include <windows.h>
#include "../matrix.h"

Matrix randomMatrix(int n) {
    Matrix m(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m.set(i, j, (rand() % 100) / 10.0);
    return m;
}

double timeNaive(const Matrix& A, const Matrix& B) {
    auto t0 = std::chrono::high_resolution_clock::now();
    Matrix R = A * B;                 
    (void)R;                          
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
double timeOpt(const Matrix& A, const Matrix& B) {
    auto t0 = std::chrono::high_resolution_clock::now();
    Matrix R = A.mulOptimized(B);     
    (void)R;
    auto t1 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}

int main() {
    SetConsoleOutputCP(65001);
    std::cout << "=== наивная (i-j-k) против оптимизированной (i-k-j) ===\n";
    std::cout << std::left << std::setw(10) << "Размер  "
        << std::setw(16) << "naive (мс)" << std::setw(16) << "opt (мс)"
        << std::setw(14) << "Ускорение" << std::endl;
    std::cout << std::string(56, '-') << std::endl;

    for (int n : {100, 200, 500, 1000}) {
        Matrix A = randomMatrix(n);
        Matrix B = randomMatrix(n);
        double tN = timeNaive(A, B), tO = timeOpt(A, B);
        std::cout << std::left << std::fixed << std::setprecision(2)
            << std::setw(10) << n
            << std::setw(16) << tN
            << std::setw(16) << tO
            << std::setw(14) << (tN / tO) << std::endl;
    }
    return 0;
}