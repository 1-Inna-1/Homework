#include "matrix.h"      
#include <iostream>     

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            os << m.get(i, j) << "\t"; 
        }
        os << "\n"; 
    }
    return os;
}