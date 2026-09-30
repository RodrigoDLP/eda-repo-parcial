#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        int n, m; cin >> m; cin >> n;
        string temp;
        vector<vector<char>> v;
        v.resize(m);
        vector<vector<pair<int, int>>> v2;
        v2.resize(m);
        unordered_map<int, int> t;
        for (int i=0; i<m; ++i) {
            cin >> temp;
            for (auto c: temp) {v[i].push_back(c); v2[i].emplace_back(0, 0);}
        }
        for (int i=0; i<m; ++i) {
            int counter = 0;
            for (int j=0; j<n; ++j) {
                if (v[i][j] == '*') ++counter;
            }
            for (int j=0; j<n; ++j) {
                v2[i][j].first = counter;
            }
        }
        for (int i=0; i<n; ++i) {
            int counter = 0;
            for (int j=0; j<m; ++j) {
                if (v[j][i] == '*') ++counter;
            }
            for (int j=0; j<m; ++j) {
                v2[j][i].second = counter;
            }

        }
        ll trianglecounter = 0;
        for (int i=0; i<m; ++i) {
            for (int j=0; j<n; ++j) {
                if (v[i][j] == '*') trianglecounter += (v2[i][j].first-1)*(v2[i][j].second-1);
            }
        }
        cout << trianglecounter << "\n";



    return 0;
}


/* SEPARATE INT INTO DIGITS
int i=0;
while (num > 0) {
    num1 = (num % (static_cast<ll>(pow(10,i+1))));
    num2 = num1 / static_cast<ll>(pow(10,i));
    num -= num1;
    //NUM2 = dígito extraído en este paso
    ++i;
}
*/