#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n; int k; cin >> k;

}


/*
solo leen: for_each (aplica lambda a v.begin(), v.end(), lambda), count, any_of, find, mismatch
copian o mueven: copy, copy_if, move, swap_ranges, transform
eliminan - compactan rango y devuelven "frontera": remove, remove_if, unique
alteran orden - reverse, rotate, fill, generate, shuffle
ordenan como tal - sort, stable_sort, partition, nth_element
conjuntos sobre rangos YA ORDENADOS - merge, set_union, set_difference
búsquedas - binary_search, lower_bound (upper_bound?), equal_range
permutaciones - next_permutation, prev_permutation
numéricos - accumulate, inner_product, partial_sum, iota

find
auto it = find(v.begin(), v.end(), 9); if (it == v.end()) return false; else return *it;

copy_if
auto fun = [](int x){return x%2==0;};
vector<int> src, dest; copy_if(src.begin(), src.end(), back_inserter(dst), fun);

remove_if (del ejemplo anterior)
auto new_end = remove_if(src.begin(), src.end(), fun);
v.erase(new_end, v.end());

rotate (siendo d un deque)
rotate(d.begin(), d.begin()+2, d.end()) //rota hacia la izq. abcde pasa a ser cdeab

stable_sort(people.begin(), people.end(), [](auto& a, auto& b){return a.age<b.age;});

//a y b vectores ORDENADOS ascendentemente
vector<int> uni;
set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(uni));

int max_val = accumulate(v.begin(), v.end(), v.front(), [](int a, int b){return a>b?a:b;});

vector<int> fib(10); int a=0, b=1; //10 primeros números de fibonacci
generate_n(fib.begin(), fib.size(), [&]{int tmp=a; a=b; b+=tmp; return tmp;});



*/