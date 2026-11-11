#include <bits/stdc++.h>
using namespace std;

int ask(int x, const vector<int>& p) {
    cout << "? " << x;

    for (int i = 1; i < (int)p.size(); ++i) {
        cout << ' ' << p[i];
    }

    cout << endl;  // Newline and flush.

    int response;
    if (!(cin >> response) || response == -1) {
        exit(0);
    }

    return response;
}

void solve() {
    int n;
    cin >> n;

    if (n == 2) {
        cout << "!\n1 2\n" << flush;
        return;
    }

    vector<int> subtree(n + 1);
    vector<int> p(n + 1);

    subtree[1] = n;

    // Phase 1: determine subtree sizes.
    for (int v = 2; v <= n; ++v) {
        p[1] = n - 1;
        p[v] = n;

        int label = 1;

        for (int u = 2; u <= n; ++u) {
            if (u != v) {
                p[u] = label++;
            }
        }

        subtree[v] = ask(1, p) - n * (n - 1);
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 1);

    sort(order.begin(), order.end(), [&](int u, int v) {
        if (subtree[u] != subtree[v]) {
            return subtree[u] > subtree[v];
        }
        return u < v;
    });

    vector<pair<int, int>> edges;
    int baseline = n * (n + 1) / 2;

    // Phase 2: identify each vertex's parent.
    for (int i = 1; i < n; ++i) {
        int v = order[i];
        p[v] = 1;

        int label = 2;

        for (int u : order) {
            if (u != v) {
                p[u] = label++;
            }
        }

        int delta = ask(v, p) - baseline;

        int r = 0;
        while (r * (r + 1) / 2 < delta) {
            ++r;
        }

        edges.push_back({order[r], v});
    }

    cout << "!\n";

    for (auto [u, v] : edges) {
        cout << u << ' ' << v << '\n';
    }

    cout << flush;
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