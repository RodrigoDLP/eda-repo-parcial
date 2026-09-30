#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

/*
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, d, k; cin >> n >> d >> k;
        vector<pair<int, bool>> v;
        for (int i=0; i<k; ++i) {
            int temp; cin >> temp; v.emplace_back(temp, false);
            cin >> temp; v.emplace_back(temp+1, true);
        }
        sort(v.begin(), v.end());
        vector<int> visitsizes(n+2);
        int count = 0, doubleindex = 0;
        for (int i=1; i<=n+1; ++i) {
            while (v[doubleindex].first == i) {
                if (v[doubleindex].second) ++count; else --count;
                ++doubleindex;
            }
            visitsizes[i] = count;
        }
        count = 0;
        int mostjobs = 0, leastjobs = INT_MAX, mostindex = -1, leastindex = -1;
        for (int i=0; i<)
    }
}*/
auto sortlambda = [](auto& a1, auto& a2){return a1.first < a2.first;};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n, d, k; cin >> n >> d >> k;
        deque<pair<int, bool>> v;
        vector<int> v2(n+1, 0), v3(n+1, 0);
        for (int i=0; i<k; ++i) {
            int temp; cin >> temp; v.emplace_back(temp, false);
            cin >> temp; v.emplace_back(temp, true);
        }
        sort(v.begin(), v.end(), sortlambda);
        ll startcounter=0, endcounter=0;
        for (int i=1; i<=n; ++i) {
            while (!v.empty() && v.front().first == i) {if (v.front().second) ++endcounter; else ++startcounter; v.pop_front();}
            v2[i] = startcounter; v3[i] = endcounter;
        }
        ll maxdif = 0, mindif = LLONG_MAX;
        int maxday = -1, minday = -1;
        for (int i=d; i<=n; ++i) {
            ll dif = v2[i] - v3[i-d];
            if (dif > maxdif) {maxdif = dif; maxday = i-d+1;}
            if (dif < mindif) {mindif = dif; minday = i-d+1;}
        }
        cout << maxday << " " << minday << "\n";

    }
}