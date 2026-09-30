#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int largestprime(int target, int k, vector<int>& primes) {
    for (int i=0; i<primes.size(); ++i) {
        if (!(k % primes[i] == 0 && k/primes[i] < target/primes[i])) {
            if (target % primes[i] == 0 && (primes[i] > k)) return primes[i];
        }
    }
    for (int i=0; i<primes.size(); ++i) {
        if (target % primes[i] == 0) return primes[i];
    }
    return target;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); int T; cin >> T;
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
    while (T--) {
        int n, k; cin >> n >> k;
        priority_queue<ll> pq; int temp;
        unordered_map<ll, ll> m;
        for (int i=0; i<n; ++i) {cin >> temp; if (!m.count(temp)) {pq.push(temp); m[temp] = 1;} else m[temp]++;}
        ll ops = 0;
        while (pq.top() > k) {
            int t = pq.top();
            ops += m[t];
            //cout << "ops=" << ops << " as t=" << t << " and m[t] = " << m[t] << "\n";

            int sp = largestprime(t, k, primes);
            int newt = t / sp;
            pq.pop();
            if (!m.count(newt) || m[newt] == 0) {
                pq.push(newt);
                m[newt] = sp * m[t];
            } else {
                m[newt] += sp * m[t];
            }
            m[t] = 0;
        }
        cout << ops << "\n";
    }
}

