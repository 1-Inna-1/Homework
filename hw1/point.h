#pragma once
#include <cmath>


struct Point {
    double x;  
    double y; 

    double distance() const {
        return std::sqrt(x * x + y * y);
    }
};

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

inline bool operator<(const Point& a, const Point& b) {
    return a.distance() < b.distance();
}

inline bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}