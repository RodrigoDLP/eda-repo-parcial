#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


//auto sort1 = [](auto& e1, auto& e2) {return e1.first < e2.first;};
auto sort1 = [](auto& e1, auto& e2) {return get<0>(e1) < get<0>(e2);};
auto sort2 = [](auto& e1, auto& e2) {return get<1>(e1) < get<1>(e2);};
auto sort3 = [](auto& e1, auto& e2) {
    return get<2>(e1) > get<2>(e2);
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, k, temp;
        cin >> n >> k;
        vector<tuple<int, int, int>> v, v2;
        for (int i=0; i<n; ++i) {cin >> temp;
            if (temp % k == 0) v2.push_back(make_tuple(i, temp, temp % k));
            else v.push_back(make_tuple(i, temp, temp % k));}
        stable_sort(v.begin(), v.end(), sort3);
        stable_sort(v2.begin(), v2.end(), sort2);
        stable_sort(v2.begin(), v2.end(), sort1);
        for (int i=0; i<v2.size(); ++i) cout << get<0>(v2[i])+1 << " ";
        for (int i=0; i<v.size(); ++i) cout << get<0>(v[i])+1 << " "; cout << "\n";
    }
    return 0;
}