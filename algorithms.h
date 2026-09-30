#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
using namespace std;

template<typename T>
void merge_sort(vector<T>& v) {

}
template<typename T>
void merge_sort_index(vector<T>& v, int p, int r) {
    if (p > r) return;
    int q = (p+r)/2;
    merge_sort_index(v, p, q);
    merge_sort_index(v, q+1, r);

}







#endif //ALGORITHMS_H
