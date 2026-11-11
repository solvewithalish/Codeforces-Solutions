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

        long long p = 0;

        for (int i = 0; i < n; ++i) {
            long long a;
            cin >> a;

            if (i % 2 == 0) {
                p += a;
            } else {
                p -= a;
            }
        }

        cout << p << '\n';
    }

    return 0;
}