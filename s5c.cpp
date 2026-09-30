#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

auto compare = [](auto& a, auto& b){return a.first < c.first;};
auto a = [](auto& a, auto& b){return a.second < b.second;};

auto a1 = [](auto& a, auto& b){return get<0>(a) < get<0>(b);};

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int temp1, temp2;
    int n; cin >> n; deque<tuple<int, bool, int>> v;
    map<int, int> m;
    for (int i=0; i<n; ++i) {cin >> temp1; v.emplace_back(temp1, true, i); cin >> temp2; v.emplace_back(temp2, false, i);}
    sort(v.begin(), v.end(), a1);
    vector<int> enumeration;
    for (int i=1; i<=n; ++i) enumeration.push_back(i);
    priority_queue<int, vector<int>, greater<int>> pq(greater<int>(), move(enumeration));
    for (int i=0; i<v.size(); ++i) {
        auto front_elem = v.front();
        auto index = get<2>(front_elem);
        if (get<1>(front_elem)) {
            m[index] = pq.top(); pq.pop();
        } else {
            pq.push(m[index]);
        }

    }




    //priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> pq;






    vector<vector<int>> output;









    int count = 0;
    while (!v.empty()) {
        int mark = v[0].second;
        ++count;
        v.pop_front();
        while (!v.empty() && v[0].first <= mark) v.pop_front();
    }
    cout << count << "\n";
}