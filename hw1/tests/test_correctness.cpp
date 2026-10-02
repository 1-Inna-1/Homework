#include <iostream>
#include <windows.h>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include <string>
#include "../mysort.h"
#include "../point.h"


template <typename T>
bool checkSorted(const std::vector<T>& original, const std::vector<T>& sorted, const std::string& testName) {
    bool isSorted = std::is_sorted(sorted.begin(), sorted.end());

    std::vector<T> sortedCopy = sorted;
    std::vector<T> originalCopy = original;
    std::sort(sortedCopy.begin(), sortedCopy.end());
    std::sort(originalCopy.begin(), originalCopy.end());
    bool isPermutation = (sortedCopy == originalCopy);

    if (isSorted && isPermutation) {
        std::cout << "[OK] " << testName << std::endl;

        if (sorted.size() <= 20) {
            std::cout << "    Отсортированный массив: ";
            for (size_t i = 0; i < sorted.size(); i++) {
                std::cout << sorted[i] << " ";
            }
            std::cout << std::endl;
        }

        return true;
    }
    else {
        std::cout << "[FAIL] " << testName << std::endl;
        if (!isSorted) std::cout << "  Результат не отсортирован!" << std::endl;
        if (!isPermutation) std::cout << "  Элементы не совпадают с оригиналом!" << std::endl;
        return false;
    }
}


// Компаратор для Point (для mySort)
struct PointCompare {
    bool operator()(const Point& a, const Point& b) const {
        return a.distanceToOrigin() < b.distanceToOrigin();
    }
};

int main() {
    SetConsoleOutputCP(65001);
    std::cout << std::unitbuf;
    int passed = 0;
    int total = 0;

    std::cout << "=== Тесты для int ===" << std::endl;

    {
        total++;
        std::vector<int> v = {};
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Пустой контейнер (int)")) passed++;
    }

    {
        total++;
        std::vector<int> v = { 42 };
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Один элемент (int)")) passed++;
    }

    {
        total++;
        std::vector<int> v = { 1, 2, 3, 4, 5 };
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Уже отсортированный (int)")) passed++;
    }

    {
        total++;
        std::vector<int> v = { 5, 4, 3, 2, 1 };
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Обратный порядок (int)")) passed++;
    }

    {
        total++;
        std::vector<int> v = { 7, 7, 7, 7, 7 };
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Все равны (int)")) passed++;
    }

    {
        total++;
        std::vector<int> v = { -3, -1, -5, 2, 0, -2, 4 };
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Отрицательные числа (int)")) passed++;
    }

    {
        total++;
        std::vector<int> v = { 3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5 };
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Повторяющиеся (int)")) passed++;
    }

    std::mt19937 rng(42);  // случайные числа
    for (int size : {10, 1000, 100000}) {
        total++;
        std::vector<int> v(size);
        std::uniform_int_distribution<int> dist(-1000000, 1000000);
        for (int i = 0; i < size; i++) {
            v[i] = dist(rng);
        }
        std::vector<int> original = v;
        mySort(v.begin(), v.end());
        if (checkSorted(original, v, "Случайные данные, размер " + std::to_string(size) + " (int)")) passed++;
    }

    std::cout << "\n=== Тесты для Point ===" << std::endl;
    {
        total++;
        std::vector<Point> v = {};
        std::vector<Point> original = v;
        mySort(v.begin(), v.end(), PointCompare{});
        if (checkSorted(original, v, "Пустой контейнер (Point)")) passed++;
    }

    {
        total++;
        std::vector<Point> v = { { 3.0, 4.0 } };
        std::vector<Point> original = v;
        mySort(v.begin(), v.end(), PointCompare{});
        if (checkSorted(original, v, "Один элемент (Point)")) passed++;
    }

    {
        total++;
        std::vector<Point> v = { { 0.0, 0.0 },{ 1.0, 0.0 },{ 3.0, 4.0 } };  // раст 0, 1, 5
        std::vector<Point> original = v;
        mySort(v.begin(), v.end(), PointCompare{});
        if (checkSorted(original, v, "Уже отсортированный (Point)")) passed++;
    }

    {
        total++;
        std::vector<Point> v = { { 3.0, 4.0 },{ 1.0, 0.0 },{ 0.0, 0.0 } };  // раст 5, 1, 0
        std::vector<Point> original = v;
        mySort(v.begin(), v.end(), PointCompare{});
        if (checkSorted(original, v, "Обратный порядок (Point)")) passed++;
    }

    {
        total++;
        std::vector<Point> v = { { 1.0, 1.0 },{ 1.0, 1.0 },{ 1.0, 1.0 } };
        std::vector<Point> original = v;
        mySort(v.begin(), v.end(), PointCompare{});
        if (checkSorted(original, v, "Все равны (Point)")) passed++;
    }

    for (int size : {10, 1000, 100000}) {
        total++;
        std::vector<Point> v(size);
        std::uniform_real_distribution<double> dist(-1000.0, 1000.0);
        for (int i = 0; i < size; i++) {
            v[i] = { dist(rng), dist(rng) };
        }
        std::vector<Point> original = v;
        mySort(v.begin(), v.end(), PointCompare{});
        if (checkSorted(original, v, "Случайные данные, размер " + std::to_string(size) + " (Point)")) passed++;
    }

    // Итого
    std::cout << "\n=== Результат: " << passed << " из " << total << " тестов пройдено ===" << std::endl;

    return (passed == total) ? 0 : 1;
}