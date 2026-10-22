#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> degree(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        ++degree[u - 1];
        ++degree[v - 1];
    }

    int leaves = 0;
    int centers = 0;

    for (int d : degree) {
        if (d == 0) {
            cout << "Brain Melt\n";
            return;
        }

        if (d == 1) ++leaves;
        if (d == n - 1) ++centers;
    }

    if (centers == 1 && leaves == n - 1) {
        cout << "2\n";
    } else {
        cout << "Many\n";
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