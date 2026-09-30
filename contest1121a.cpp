#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int m; cin>> m;
        vector<ll> v(n);
        for (int i=0; i<n; ++i) cin >> v[i];
        if (m == 1) {
            ll maxelem = LLONG_MIN;
            for (int i=0; i<n; ++i) if (v[i] > maxelem) maxelem = v[i];
            cout << maxelem << "\n";
            continue;
        }
        priority_queue<ll> pq;
        vector<ll> maxvals;
        ll pqsum = 0;
        for (int i=0; i<m-1; ++i) {pq.push(v[i]); pqsum += v[i];}
        maxvals.push_back(pqsum); //elem for i = m
        for (int i=m-1; i<n; ++i) { //for m+1 and so on
            if (v[i] < pq.top()) {
                pqsum += v[i];
                pqsum -= pq.top();
                pq.pop();
                pq.push(v[i]);
            }
            maxvals.push_back(pqsum);
        } //one extra element at the end
        //for (auto e: maxvals) cout << e << " "; cout << "\n";
        ll maxoutput = LLONG_MIN;
        for (int i=m-1; i<n; ++i) {
            //if (i-(m-1) < 0) throw runtime_error(":(");
            //if (i < 0) throw runtime_error(":(1");
            //if (i-(m-1) >= maxvals.size()) throw runtime_error(":(2");
            ll calc =  m*v[i]-maxvals[i-(m-1)];
            if (calc > maxoutput) {
                maxoutput = calc;
                //cout << "new max output found - i=" << i << " v[i]=" << v[i] << "maxvals[i-m]=" << maxvals[i-(m-1)] << "\n";
            }
        }
        cout << maxoutput << "\n";
    }
}