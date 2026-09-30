#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        int K; cin >> K;
        if (K > N-2 || K < 0 || N < 0) cout << "-1\n";
        else if (N == 0) cout << "\n";
        else if (N == 1) cout << "1\n";
        else {
            string output = "01";
            for (int i = 0; i<K/2; ++i) {
                output = "0" + output;
                output = output + "1";
            }
            int sz = K+2;
            if (K % 2 == 1 && N % 2 == 1) {
                output = "0" + output;
                sz++;
            } else if (N % 2 == 1) {
                output = "1" + output;
                sz++;
            } else if (K % 2 == 1) {
                output = "10" + output;
                sz += 2;
            }

            for (int i=sz; i<N; i += 2) output += "01";
            cout << output << "\n";
        }

    }
    return 0;
}