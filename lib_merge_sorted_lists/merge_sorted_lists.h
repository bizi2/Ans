#include <iostream>
#include <list>
#include <vector>
#include <cassert>

std::list<int> mergeSortedLists(const std::list<int>& list1, const std::list<int>& list2) {
    std::list<int> mergedList;
    auto it1 = list1.begin();
    auto it2 = list2.begin();

    while (it1 != list1.end() && it2 != list2.end()) {
        if (*it1 < *it2) {
            mergedList.push_back(*it1);
            ++it1;
        } else {
            mergedList.push_back(*it2);
            ++it2;
        }
    }

    while (it1 != list1.end()) {
        mergedList.push_back(*it1);
        ++it1;
    }

    while (it2 != list2.end()) {
        mergedList.push_back(*it2);
        ++it2;
    }

    return mergedList;
}
