#pragma once
#include <vector>
#include <functional>
#include <iterator>


template <typename It, typename Compare = std::less<typename std::iterator_traits<It>::value_type>>
void mySort(It first, It last, Compare comp = Compare{}) {
    auto n = std::distance(first, last);
    if (n <= 1) return;

    auto mid = first;
    std::advance(mid, n / 2);
    mySort(first, mid, comp);
    mySort(mid, last, comp);

    std::vector<typename std::iterator_traits<It>::value_type> left(first, mid);  
    std::vector<typename std::iterator_traits<It>::value_type> right(mid, last);


    auto res = first;         
    auto l_index = left.begin();   
    auto l_end = left.end();    
    auto r_index = right.begin(); 
    auto r_end = right.end();   

    while (l_index != l_end && r_index != r_end) {
        if (comp(*r_index, *l_index)) {
            *res = *r_index;
            ++r_index;
        }
        else {
            *res = *l_index;
            ++l_index;
        }
        ++res;
    }

    while (l_index != l_end) {
        *res = *l_index;
        ++l_index;
        ++res;
    }

    while (r_index != r_end) {
        *res = *r_index;
        ++r_index;
        ++res;
    }
}