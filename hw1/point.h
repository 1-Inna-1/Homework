#pragma once
#include <cmath>


struct Point {
    double x;  
    double y; 

    double distanceToOrigin() const {
        return std::sqrt(x * x + y * y); // расстояние от точки до начала координат
    }
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

inline bool operator<(const Point& a, const Point& b) {
    return a.distanceToOrigin() < b.distanceToOrigin();
}

inline bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}