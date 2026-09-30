#include <bits/stdc++.h>
#include <tuple>
using namespace std;
typedef long long ll;


auto tuple_sort3 = [](const auto& t1, const auto& t2) {return std::get<3>(t1) < std::get<3>(t2);};
auto tuple_sort2 = [](const auto& t1, const auto& t2) {return std::get<2>(t1) < std::get<2>(t2);};
auto tuple_sort1 = [](const auto& t1, const auto& t2) {return std::get<1>(t1) < std::get<1>(t2);};
auto tuple_sort2desc = [](const auto& t1, const auto& t2) {return std::get<2>(t1) > std::get<2>(t2);};
auto tuple_sort1desc = [](const auto& t1, const auto& t2) {return std::get<1>(t1) > std::get<1>(t2);};

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    string s;
    int temp, temp2, temp3, temp4;
    for (int test=1; test<=T; ++test) {
        int n; cin >> n;
        std::vector<std::tuple<int, int, int, char>> v;
        std::vector<std::tuple<int, int, int>> v2;
        cin >> temp;
        for (int i=0; i<n; ++i) {
            cin >> temp; cin >> temp2; cin >> temp3; cin >> temp4;
            v.emplace_back(temp, temp2, temp3, temp4);
        }
        bool skipping = false;
        int c0 = 0;
        int c1 = 0;
        map<int, pair<int, int>> penalty;
        sort(v.begin(), v.end(), tuple_sort3);
        sort(v.begin(), v.end(), tuple_sort2);
        sort(v.begin(), v.end(), tuple_sort1);
        for (const auto& t: v) {
            if (!penalty.count[get<0>(t)]) penalty[get<0>(t)] = make_pair(0, 0);
            if (c0 != get<0>(t) || c1 != get<1>(t)) skipping = false;
            if (!skipping) {
                if (get<3>(t) == 'C') {
                    skipping = true;
                    (penalty[get<0>(t)].first)++;
                    penalty[get<0>(t)].second += get<2>(t);
                }
                else if (get<3>(t) == 'I') penalty[get<0>(t)].second += 20;
            }
        }
        for (const auto& e: penalty) v2.emplace_back(e.first, e.second.first, e.second.second);
        sort(v2.begin(), v2.end(), tuple_sort2desc);
        sort(v2.begin(), v2.end(), tuple_sort1desc);
        for (auto t: v2) {
            cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << "\n";
        }
    }
    return 0;
}