#pragma once                 
#include <vector>         
#include <iostream>          

class Matrix {

private:                    
    std::vector<std::vector<double>> data;
    int n;

public:                 
    Matrix(int size) {
        n = size;                      
        data.resize(size);              
        for (int i = 0; i < size; i++)
            data[i].resize(size);   
    }
    int size() const { return n; }     
    double get(int r, int c) const { return data[r][c]; }  
    void   set(int r, int c, double v) { data[r][c] = v; } 

    Matrix operator+(const Matrix& other) const {
        Matrix result(n);                      
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result.set(i, j, get(i, j) + other.get(i, j)); 
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix result(n);

        for (int i = 0; i < n; i++) {        
            for (int j = 0; j < n; j++) {           
                double sum = 0.0;           
                for (int k = 0; k < n; k++) {       
                    sum += get(i, k) * other.get(k, j);
                }
                result.set(i, j, sum);             
            }
        }
        return result;
    }

    Matrix mulOptimized(const Matrix& other) const {
        Matrix result(n);
        for (int i = 0; i < n; i++) {    
            const std::vector<double>& rowA = data[i];  
            std::vector<double>& rowR = result.data[i]; 
            for (int k = 0; k < n; k++) { 
                double a = rowA[k];                
                const std::vector<double>& rowB = other.data[k]; 
                for (int j = 0; j < n; j++)   
                    rowR[j] += a * rowB[j];
            }
        }
        return result;
    }
};

std::ostream& operator<<(std::ostream& os, const Matrix& m);