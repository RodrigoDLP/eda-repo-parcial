#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        ll num, num1, num2; cin >> num;
        if (num == 0) cout << 0 << "\n";
        else {
            ll minnum = 10;
            int i=0;
            while (num > 0) {
                //cout << "#1. i=" << i << endl;
                num1 = (num % (
                    static_cast<ll>(pow(10,i+1))
                    ));
                //cout << "#2. i=" << i << endl;
                num2 = num1 / static_cast<ll>(pow(10,i));
                //cout << "#3. i=" << i << endl;
                num -= num1;
                if (num2 < minnum) minnum = num2;
                //cout << "#4. i=" << i << " num=" << num << endl;
                ++i;
            }
            cout << minnum << "\n";
        }
    }

    return 0;
}