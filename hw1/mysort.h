#pragma once
#include <vector>
#include <functional>
#include <iterator>


template <typename It, typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void mySort(It first, It last, Compare comp = Compare{}) {
    // Считаем, сколько элементов между first и last
    auto n = std::distance(first, last);

    if (n <= 1) return;

    auto mid = first;
    std::advance(mid, n / 2);  // сдвигаем итератор на n/2 позиций вперёд

    // Рекурсивно сортируем левую половину (от first до mid)
    mySort(first, mid, comp);
    // Рекурсивно сортируем правую половину (от mid до last)
    mySort(mid, last, comp);

    // Теперь обе половины отсортированы. Нужно их "слить" в одну.
    // Копируем элементы во временные векторы
    using ValueType = typename std::iterator_traits<It>::value_type;
    std::vector<ValueType> left(first, mid);   // левая половина
    std::vector<ValueType> right(mid, last);   // правая половина

    // Слияние: берём меньший элемент из left или right и кладём в результат
    auto it = first;          // куда пишем результат
    auto li = left.begin();   // текущая позиция в left
    auto le = left.end();     // конец left
    auto ri = right.begin();  // текущая позиция в right
    auto re = right.end();    // конец right

    // Пока в обеих половинах есть элементы
    while (li != le && ri != re) {
        // Если элемент из right меньше элемента из left (по нашему компаратору)
        if (comp(*ri, *li)) {
            *it = *ri;   // берём из right
            ++ri;
        }
        else {
            *it = *li;   // берём из left
            ++li;
        }
        ++it;
    }

    // Если в left остались элементы — докопировать их
    while (li != le) {
        *it = *li;
        ++li;
        ++it;
    }

    // Если в right остались элементы — докопировать их
    while (ri != re) {
        *it = *ri;
        ++ri;
        ++it;
    }
}