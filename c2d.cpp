#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// <>, <<, >>
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    string temp;
    stack<ll> s; s.push(0);
    stack<ll> repeats; repeats.push(1);
    bool overflow = false;
    ll actualmax = INT_MAX;
    actualmax *= 2;
    actualmax += 1;
    //ll actualmaxtest = INT_MAX * 2 + 1;
    //cout << actualmax << "\n";
    //cout << pow(2, 32) << "\n";
    int i=0;
    while (i < n) {
        cin >> temp;
        if (temp[0] == 'a') {
            ll counter = s.top();
            s.pop();
            counter++;
            if (counter < 0 || counter > actualmax) overflow = true;
            s.push(counter);
        } else if (temp[0] == 'f') {
            ll num; cin >> num;
            if (num > actualmax) overflow = true;
            repeats.push(num);
            s.push(0);
        } else if (temp[0] == 'e') {
            ll num = s.top() * repeats.top();
            if (num < 0 || num > actualmax) overflow = true;
            s.pop(); repeats.pop();

                ll counter = s.top();
                s.pop();
                ll sum = counter + num;
                if (sum < 0 || sum > actualmax) overflow = true;
                s.push(sum);

        }
        ++i;
    }
    if (overflow || s.top() > actualmax) cout << "OVERFLOW!!!\n";
    else cout << s.top() << "\n";
}