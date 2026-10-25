#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;

    bool canIncrease = false;
    bool canDecrease = false;

    for (int i = 1; i + 1 < (int)s.size(); ++i) {
        if (s[i - 1] == s[i + 1]) {
            if (s[i] == s[i - 1]) {
                canIncrease = true;
            } else {
                canDecrease = true;
            }
        }
    }

    cout << 1 + canIncrease + canDecrease << '\n';
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