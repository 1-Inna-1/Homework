#include <iostream>
#include <vector>
#include <cmath>            
#include <stdexcept>        
#include <string>           
#include <windows.h>       
#include "../matrix.h"     

bool sravnenie_matrix(const Matrix& a, const Matrix& b, double tol = 1e-9) {
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < a.size(); j++)
            if (std::fabs(a.get(i, j) - b.get(i, j)) > tol)
                return false;
    return true;
}

Matrix randomMatrix(int n) {
    Matrix m(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m.set(i, j, (rand() % 100) / 10.0);
    return m;
}



int main() {
    SetConsoleOutputCP(65001);


    // ===== Тест 1: A * I = A =====
    {
        Matrix A({{1,2},{3,4}});
        Matrix I({{1,0},{0,1}});
        Matrix R = A * I;
        std::cout << "--- Тест 1: A * I = A ---\n";
        std::cout << "A:\n" << A << "\n";
        std::cout << "I:\n" << I << "\n";
        std::cout << "A * I =\n" << R << "\n";
    }

    // ===== Тест 2: A * 0 = 0 =====
    {
        Matrix A({{1,2},{3,4}});
        Matrix Z(2);                      
        Matrix R = A * Z;
        std::cout << "--- Тест 2: A * 0 = 0 ---\n";
        std::cout << "A:\n" << A << "\n";
        std::cout << "Z:\n" << Z << "\n";
        std::cout << "A * Z =\n" << R << "\n";
    }

    // =========== Тест 3 ==========
    {
        Matrix A({{1,2},{3,4}});
        Matrix B({{5,6},{7,8}});
        Matrix expected({{19,22},{43,50}});
        Matrix R = A * B;
        std::cout << "--- Тест 3: 2x2 ---\n";
        std::cout << "A:\n" << A << "\n";
        std::cout << "B:\n" << B << "\n";
        std::cout << "A * B (получилось)\n" << R << "\n";
        std::cout << "A * B (ожидалось):\n" << expected << "\n";
    }

    // ===== Тест 4: сложение =====
    {
        Matrix A({{1,2},{3,4}});
        Matrix B({{10,20},{30,40}});
        Matrix expected({{11,22},{33,44}});
        Matrix R = A + B;
        std::cout << "--- Тест 4: A + B ---\n";
        std::cout << "A:\n" << A << "\n";
        std::cout << "B:\n" << B << "\n";
        std::cout << "A + B (получилось)\n" << R << "\n";
        std::cout << "A + B (ожидалось):\n" << expected << "\n";
    }

    // ========= Тест 5: ==========
    {
        Matrix A(2), B(3);
        std::cout << "--- Тест 5: 2x2 * 3x3 должно бросить исключение ---\n";
        std::cout << "A:\n" << A << "\n";
        std::cout << "B:\n" << B << "\n";
        bool threw = false;
        try { 
            Matrix R = A * B;
            (void)R; 
        }
        catch (const std::invalid_argument&) {
            threw = true; 
        }
        if (threw) {
            std::cout << "[OK] Исключение поймано, мусора нет\n\n";
        }
        else {
            std::cout << "[FAIL] Исключения не было!\n\n";
        }
    }

    for (int n : {2, 3, 5, 8}) {
        Matrix A = randomMatrix(n);
        Matrix B = randomMatrix(n);
        Matrix naive = A * B;
        Matrix opt = A.mulOptimized(B);
        bool ok = sravnenie_matrix(naive, opt);
        std::cout << "--- Тест 6: naive == optimized, n=" << n << " ---\n";
        std::cout << "A:\n" << A << "\n";
        std::cout << "B:\n" << B << "\n";
        std::cout << "naive (i-j-k) =\n" << naive << "\n";
        std::cout << "optimized (i-k-j) =\n" << opt << "\n";
    }
}