#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
constexpr ll MOD = 1000000007;
 
ll normalize(ll x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n, m;
        cin >> n >> m;
 
        ll answer = 0;
 
        if (n % 2 == 1) {
            // Sum each column over odd-numbered rows.
            vector<ll> column(m, 0);
 
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    ll x;
                    cin >> x;
 
                    if (i % 2 == 0) {
                        column[j] = (column[j] + normalize(x)) % MOD;
                    }
                }
            }
 
            ll oddPrefix = 0;
 
            for (int j = 0; j < m; ++j) {
                if (j % 2 == 0) {
                    oddPrefix = (oddPrefix + column[j]) % MOD;
                } else if (m % 2 == 0) {
                    answer = (answer + oddPrefix * column[j]) % MOD;
                }
            }
 
            if (m % 2 == 1) {
                answer = oddPrefix * oddPrefix % MOD;
            } else {
                answer = normalize(-2 * answer);
            }
        } else if (m % 2 == 1) {
            ll oddRowPrefix = 0;
 
            for (int i = 0; i < n; ++i) {
                ll rowSum = 0;
 
                for (int j = 0; j < m; ++j) {
                    ll x;
                    cin >> x;
 
                    if (j % 2 == 0) {
                        rowSum = (rowSum + normalize(x)) % MOD;
                    }
                }
 
                if (i % 2 == 0) {
                    oddRowPrefix = (oddRowPrefix + rowSum) % MOD;
                } else {
                    answer = (answer + oddRowPrefix * rowSum) % MOD;
                }
            }
 
            answer = normalize(-2 * answer);
        } else {
            // Column sums over previously processed odd-numbered rows.
            vector<ll> top(m, 0);
            ll totalEvenColumns = 0;
 
            for (int i = 0; i < n; ++i) {
                ll leftOdd = 0;
                ll rightEven = totalEvenColumns;
 
                for (int j = 0; j < m; ++j) {
                    ll x;
                    cin >> x;
                    x = normalize(x);
 
                    if (i % 2 == 0) {
                        top[j] = (top[j] + x) % MOD;
 
                        if (j % 2 == 1) {
                            totalEvenColumns =
                                (totalEvenColumns + x) % MOD;
                        }
                    } else if (j % 2 == 0) {
                        leftOdd = (leftOdd + top[j]) % MOD;
                        answer = (answer + x * rightEven) % MOD;
                    } else {
                        rightEven = normalize(rightEven - top[j]);
                        answer = (answer + x * leftOdd) % MOD;
                    }
                }
            }
 
            answer = 2 * answer % MOD;
        }
 
        cout << answer << '
';
    }
 
    return 0;
}