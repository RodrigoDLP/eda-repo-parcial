#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;



auto sortsecond = [](auto& a, auto& b){if (a.first != b.first) return a.first < b.first; return a.second > b.second;};

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n; int temp;
        //unordered_set<ll> nums;
        deque<pair<int, int>> v;
        deque<pair<int, int>> v2;
        v.emplace_back(n, n+1);



        for (int i=0; i<n; ++i) {
            cin >> temp;
            for (int i2=0; i2 < temp; ++i2) v2.emplace_back(i*i2, i*(i2+1)-1);

            ll a = temp * (i+1);
            //if (a == 0) continue;
            if (a >= n) {}//nums.insert(n); //
            else {
                //nums.insert(a);
                //for (int i1=a; i1<a+(i+1); ++i1) nums.insert(i1);
                v.emplace_back(a, a+(i+1)-1);
            }
        }
        sort(v.begin(), v.end(), sortsecond);
        vector<int> output2;
        int index = 0;
        while (!v.empty()) {
            auto toppair = v.front(); v.pop_front();
            //cout << "toppair = (" << toppair.first << ", " << toppair.second <<")\n";
            while (!v.empty() && v.front().first >= toppair.first && v.front().second <= toppair.second) v.pop_front();
            while (index < toppair.first) {output2.push_back(index); ++index;}
            index = toppair.second + 1;
        }

        cout << output2.size() << "\n";
        for (auto e: output2) cout << e << " "; cout << "\n";


        /*
        vector<ll> output;
        for (int i=0; i<n; ++i) {if (!nums.count(i)) output.push_back(i);}
        cout << output.size() << "\n";
        for (auto e: output) cout << e << " "; cout << "\n";
        */

    }
}