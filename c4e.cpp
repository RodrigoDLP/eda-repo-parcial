#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, k, A, B; cin >> n>> k >> A >> B;
    ll temp; //vector<ll> av(n, 0);
    vector<ll> segmenttreediy((1<<n)*2-1, 0);
    for (ll i=0; i<k; ++i) {
        cin >> temp; //av[temp-1]++;
        ll j=temp-2+(1<<n);
        while (j>0) {
            segmenttreediy[j]++;
            j = (j-1)/2;
        }
        segmenttreediy[0]++;
    }
    //if (B<=A) {cout << B*k << "\n"; return 0;}
    if (B <= A) {
        for (ll i=0; i<(1<<n)*2-1; ++i) if (i < (1<<n)-1 && (segmenttreediy[i] == 1 || segmenttreediy[i] == -1)) {
            segmenttreediy[2*i+1] = -1; segmenttreediy[2*i+2] = -1;
        }
        ll zerocount = 0, squarecount = 0;;
        for (ll i=0; i<2*(1<<n)-1; ++i) {if (segmenttreediy[i] == 1) zerocount++; else if (segmenttreediy[i] != -1 && i >= (1<<n)-1) squarecount++;}
        cout << zerocount*B+(k*B << "\n";
        return 0;
    }
    for (ll i=0; i<(1<<n)*2-1; ++i) if (i < (1<<n)-1 && (segmenttreediy[i] == 0 || segmenttreediy[i] == -1)) {
        segmenttreediy[2*i+1] = -1; segmenttreediy[2*i+2] = -1;
    }

    //for (ll i=0; i<(1<<n)*2-1; ++i) cout << segmenttreediy[i] << " "; cout << "\n";

    ll zerocount = 0, squarecount = 0;;
    for (ll i=0; i<2*(1<<n)-1; ++i) {if (segmenttreediy[i] == 0) zerocount++; else if (segmenttreediy[i] > 0 && i >= (1<<n)-1) squarecount++;}

    //cout << "zerocount: " << zerocount << " squarecount: " << squarecount << "\n";
    cout << zerocount*A+k*B << "\n";
    return 0;
}