#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n1, n2, n3; cin >> n1; cin >> n2; cin >> n3;
    queue<int> s1, s2, s3; int temp;
    ll suma1 = 0, suma2=0, suma3=0;
    for (int i=0; i<n1; ++i) {cin >> temp; s1.push(temp); suma1 += temp;}
    for (int i=0; i<n2; ++i) {cin >> temp; s2.push(temp); suma2 += temp;}
    for (int i=0; i<n3; ++i) {cin >> temp; s3.push(temp); suma3 += temp;}

    while (suma1 != suma2 || suma2 != suma3) {
        int mintop = max({suma1, suma2, suma3});
        if (mintop == suma1) {int popped = s1.front(); s1.pop(); suma1 -= popped;}
        else if (mintop == suma2) {int popped = s2.front(); s2.pop(); suma2 -= popped;}
        else if (mintop == suma3) {int popped = s3.front(); s3.pop(); suma3 -= popped;}
    }
    cout << suma1 << "\n";
}
