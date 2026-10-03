#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include "../mysort.h"
#include "../point.h"


struct PointCompare {
    bool operator()(const Point& a, const Point& b) const {
        return a.distance() < b.distance();
    }
};


template <typename T, typename Compare>
double measureTime(std::vector<T> data, Compare comp) {
    auto start = std::chrono::high_resolution_clock::now();
    mySort(data.begin(), data.end(), comp);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

template <typename T>
double measureTimeStd(std::vector<T> data) {
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(data.begin(), data.end());
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

int main() {
    SetConsoleOutputCP(65001);
    std::mt19937 rng(123);

    std::cout << "=== Бенчмарк для int ===" << std::endl;
    std::cout << std::left << std::setw(12) << "Размер"
        << std::setw(15) << "mySort (мс)"
        << std::setw(15) << "std::sort (мс)"
        << std::setw(15) << "Отношение" << std::endl;
    std::cout << std::string(57, '-') << std::endl;

    for (int size : {1000, 10000, 100000, 1000000}) {
        std::vector<int> v(size);
        std::uniform_int_distribution<int> dist(-1000000, 1000000);
        for (int i = 0; i < size; i++) {
            v[i] = dist(rng);
        }

        double myTime = measureTime(v, std::less<int>{});
        double stdTime = measureTimeStd(v);
        double ratio = myTime / stdTime;

        std::cout << std::left << std::setw(12) << size
            << std::fixed << std::setprecision(2)
            << std::setw(15) << myTime
            << std::setw(15) << stdTime
            << std::setw(15) << ratio << std::endl;
    }

    std::cout << "\n=== Бенчмарк для Point ===" << std::endl;
    std::cout << std::left << std::setw(12) << "Размер "
        << std::setw(15) << "mySort (мс)"
        << std::setw(15) << "std::sort (мс)"
        << std::setw(15) << "Отношение" << std::endl;
    std::cout << std::string(57, '-') << std::endl;

    for (int size : {1000, 10000, 100000, 1000000}) {
        std::vector<Point> v(size);
        std::uniform_real_distribution<double> dist(-1000.0, 1000.0);
        for (int i = 0; i < size; i++) {
            v[i] = { dist(rng), dist(rng) };
        }

        double myTime = measureTime(v, PointCompare{});

        auto start = std::chrono::high_resolution_clock::now();
        std::vector<Point> v2 = v;
        std::sort(v2.begin(), v2.end(), PointCompare{});
        auto end = std::chrono::high_resolution_clock::now();
        double stdTime = std::chrono::duration<double, std::milli>(end - start).count();

        double ratio = myTime / stdTime;

        std::cout << std::left << std::setw(12) << size
            << std::fixed << std::setprecision(2)
            << std::setw(15) << myTime
            << std::setw(15) << stdTime
            << std::setw(15) << ratio << std::endl;
    }

    std::cout << "\n=== Бенчмарк на отсортированном массиве (int, 100000) ===" << std::endl;
    {
        int size = 100000;
        std::vector<int> v(size);
        for (int i = 0; i < size; i++) v[i] = i; 

        double myTime = measureTime(v, std::less<int>{});
        double stdTime = measureTimeStd(v);

        std::cout << "mySort:    " << std::fixed << std::setprecision(2) << myTime << " мс" << std::endl;
        std::cout << "std::sort: " << stdTime << " мс" << std::endl;
        std::cout << "Отношение: " << myTime / stdTime << std::endl;
        std::cout << "(Merge sort нормально работает на отсортированных данных, " << std::endl;
        std::cout << " в отличие от quicksort)" << std::endl;
    }

    return 0;
}