#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr);
    int n, M; cin >> n >> M;
    vector<int> v(n);
    vector<int> cum(n+1, 0);
    vector<int> dp(n+1, 0);
    for (int i=0; i<n; ++i) {cin >> v[i]; cum[i+1] = v[i] + cum[i];}
    cout << "we are fine\n";
    for (int i=1; i<=n; ++i) {
        int lo = 1; int hi = i;
        cout << "still fine\n";
        while (lo < hi) {
            cout << "iteration. lo=" << lo << " hi=" << hi << "\n";
            int mi = lo + (hi-lo)/2;
            cout << "mi=" << mi << "\n";
            int npages1 = cum[i]-cum[mi-1]; //mi:i
            int npages2 = cum[i]-cum[mi]; //mi+1:i
            cout << "npages1: " << npages1 << " npages2: " << npages2 << "\n";
            cout << "dp[mi-1]: " << dp[mi-1] << "dp[mi]: " << dp[mi] << "\n";
            cout << "partial for mi=" << mi << ": " << npages1*npages1+dp[mi-1] << " and for mi=" << mi+1 << ": " << npages2*npages2+dp[mi] << "\n";
            if (npages1*npages1+dp[mi-1] > npages2*npages2+dp[mi]) {lo = mi+1; cout << "up\n";}
            else {hi = mi; cout << "down\n";}
        }
        cout << "optimal index j for i=" << i << " found to be " << lo << "\n";
        int npages = cum[i]-cum[lo-1];
        dp[i] = dp[lo-1]+npages*npages + M;
    }
    for (int i=1; i<dp.size(); ++i) cout << "dp[" << i << "]: " << dp[i] << " "; cout << "\n";
    cout << dp[n] << "\n";

}