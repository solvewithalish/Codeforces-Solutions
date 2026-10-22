#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    int n;
    string s;
    cin >> n >> s;
 
    s = " " + s; // 1-based indexing
 
    // nxt[i][d]: first occurrence of digit d at or after i.
    // n + 1 means that the digit does not occur.
    vector<array<int, 10>> nxt(n + 2);
    nxt[n + 1].fill(n + 1);
 
    for (int i = n; i >= 1; --i) {
        nxt[i] = nxt[i + 1];
        nxt[i][s[i] - '0'] = i;
    }
 
    vector<long long> slopeDiff(n + 3, 0);
    vector<long long> constantDiff(n + 3, 0);
 
    // Add slope * i + constant to every position i in [l, r].
    auto addRange = [&](int l, int r,
                        long long slope, long long constant) {
        if (l > r) return;
 
        slopeDiff[l] += slope;
        slopeDiff[r + 1] -= slope;
 
        constantDiff[l] += constant;
        constantDiff[r + 1] -= constant;
    };
 
    for (int l = 1; l <= n; ++l) {
        int p = nxt[l][2];
        if (p > n) continue;
 
        p = nxt[p + 1][0];
        if (p > n) continue;
 
        p = nxt[p + 1][2];
        if (p > n) continue;
 
        int L = nxt[p + 1][5];
        int R = nxt[p + 1][6] - 1;
 
        if (L > R) continue;
 
        // Positions l ... L belong to all these bad substrings.
        addRange(l, L, 0, R - L + 1);
 
        // Position i in L+1 ... R belongs to R-i+1 of them.
        addRange(L + 1, R, -1, R + 1);
    }
 
    long long slope = 0;
    long long constant = 0;
 
    for (int i = 1; i <= n; ++i) {
        slope += slopeDiff[i];
        constant += constantDiff[i];
 
        long long bad = slope * i + constant;
        long long total = 1LL * i * (n - i + 1);
 
        cout << total - bad << (i == n ? '
' : ' ');
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        solve();
    }
 
    return 0;
}