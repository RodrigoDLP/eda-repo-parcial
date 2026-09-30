#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    ll elem1, elem2;
    stack<ll> s; string temp;
    for (int i=0; i<n; ++i) {
        cin >> temp;
        if (temp == "+") {
            elem2=s.top(); s.pop();
            elem1=s.top();s.pop();
            s.push(elem1+elem2);
        }
        else if (temp == "-") {
            elem2=s.top(); s.pop();
            elem1=s.top();s.pop();
            ll result = elem1-elem2;
            s.push(result);
        }
        else if (temp == "*") {
            elem2=s.top(); s.pop();
            elem1=s.top();s.pop();
            s.push(elem1*elem2);
        }
        else if (temp == "/") {
            elem2=s.top(); s.pop();
            elem1=s.top();s.pop();
            s.push(elem1/elem2);
        }
        else {
            ll number = stoll(temp);
            s.push(number);
        }
    }
    cout << s.top() << "\n";
}



