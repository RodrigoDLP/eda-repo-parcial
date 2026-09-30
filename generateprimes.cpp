#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    vector<int> primevector;
    for (int i=3; i<=ceil(sqrt(1000000)); ++i) {
        bool result = true;
        for (int j=2; j<=ceil(sqrt(i)); ++j) {
            if (i % j == 0) {result = false; break;}
        }
        if (result) primevector.push_back(i);
    }
    cout <<"{";
    for (auto e: primevector) cout << e << ", ";
}