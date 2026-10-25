#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        long long first;
        cin >> first;

        long long low = first;
        long long high = first;
        long long answer = first;

        for (int i = 1; i < n; ++i) {
            long long x;
            cin >> x;

            long long best = x + max(abs(low), abs(high));
            answer = max(answer, best);

            long long newLow = x + min(0LL, 2 * low);
            long long newHigh = x + max(0LL, 2 * high);

            low = newLow;
            high = newHigh;
        }

        cout << answer << '\n';
    }

    return 0;
}