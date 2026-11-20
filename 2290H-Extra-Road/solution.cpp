#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> rds(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        rds[u].push_back(v);
        rds[v].push_back(u);
    }

    // Root the tree at vertex 1.
    vector<int> parent(n + 1, 0);
    vector<int> sz(n + 1, 1);
    vector<int> order;

    order.reserve(n);
    order.push_back(1);
    parent[1] = -1;

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];

        for (int v : rds[u]) {
            if (v == parent[u]) continue;

            parent[v] = u;
            order.push_back(v);
        }
    }

    // Calculate subtree sizes.
    for (int i = n - 1; i > 0; i--) {
        int u = order[i];
        sz[parent[u]] += sz[u];
    }

    // Check whether all important edges
    // can be covered by one simple path.
    auto good = [&](int x) -> bool {

        vector<int> marked(n + 1, 0);
        vector<int> cnt(n + 1, 0);

        int total = 0;

        // Mark both endpoints of important edges.
        for (int v = 2; v <= n; v++) {
            if (sz[v] > x) {
                marked[v] = 1;
                marked[parent[v]] = 1;
            }
        }

        // Initialize marked vertex counts.
        for (int v = 1; v <= n; v++) {
            cnt[v] = marked[v];
            total += marked[v];
        }

        if (total == 0) {
            return true;
        }

        // Calculate marked vertices in each subtree.
        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            cnt[parent[u]] += cnt[u];
        }

        // Check the degree in the minimal subtree
        // connecting all marked vertices.
        for (int u = 1; u <= n; u++) {

            int degree = 0;

            // Directions towards child subtrees.
            for (int v : rds[u]) {
                if (parent[v] == u && cnt[v] > 0) {
                    degree++;
                }
            }

            // Direction towards the parent.
            if (total - cnt[u] > 0) {
                degree++;
            }

            if (degree > 2) {
                return false;
            }
        }

        return true;
    };

    // Binary search for minimum feasible x.
    int lo = 0;
    int hi = n;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (good(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    int rch = n - lo;

    cout << rch << '\n';
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
