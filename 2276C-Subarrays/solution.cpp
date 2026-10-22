#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> pref(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        long long x;
        cin >> x;
        pref[i] = (pref[i - 1] + x) % k;
    }

    vector<int> frequency(k, 0);
    long long answer = 0;

    for (int r = k + 1; r <= n; ++r) {
        // This prefix now gives a subarray of length k + 1.
        ++frequency[pref[r - k - 1]];

        // All stored prefixes give lengths strictly greater than k.
        answer += frequency[pref[r]];
    }

    cout << answer << '\n';
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