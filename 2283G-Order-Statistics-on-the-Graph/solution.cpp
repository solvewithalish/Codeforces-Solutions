#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<int> k(n), incoming(n);
    for (int &x : k) cin >> x;

    while (m--) {
        int u, v;
        cin >> u >> v;
        incoming[v - 1] |= 1 << (u - 1);
    }

    const int S = 1 << n;
    vector<vector<int>> jump(n, vector<int>(S));
    vector<int> indeg(S);

    for (int mask = 0; mask < S; ++mask) {
        int to = 0;
        for (int v = 0; v < n; ++v) {
            if (__builtin_popcount(mask & incoming[v]) >= k[v])
                to |= 1 << v;
        }
        jump[0][mask] = to;
        ++indeg[to];
    }

    // Remove non-cycle states, keeping their removal order.
    vector<int> peeled;
    for (int u = 0; u < S; ++u)
        if (indeg[u] == 0) peeled.push_back(u);

    for (size_t i = 0; i < peeled.size(); ++i) {
        int v = jump[0][peeled[i]];
        if (--indeg[v] == 0) peeled.push_back(v);
    }

    // Store each cycle consecutively in successor order.
    vector<int> depth(S), pos(S), base(S), length(S), cycle;
    for (int u = 0; u < S; ++u) {
        if (!indeg[u] || length[u]) continue;

        int start = cycle.size(), v = u;
        do {
            base[v] = start;
            pos[v] = cycle.size();
            cycle.push_back(v);
            v = jump[0][v];
        } while (v != u);

        int len = (int)cycle.size() - start;
        for (int i = start; i < (int)cycle.size(); ++i)
            length[cycle[i]] = len;
    }

    vector<int> entry(S);
    for (int u : cycle) entry[u] = u;

    for (auto it = peeled.rbegin(); it != peeled.rend(); ++it) {
        int u = *it, v = jump[0][u];
        depth[u] = depth[v] + 1;
        entry[u] = entry[v];
    }

    for (int j = 1; j < n; ++j)
        for (int u = 0; u < S; ++u)
            jump[j][u] = jump[j - 1][jump[j - 1][u]];

    auto advance = [&](int u, long long t) {
        if (t < depth[u]) {
            int steps = (int)t;
            while (steps) {
                int j = __builtin_ctz(steps);
                u = jump[j][u];
                steps &= steps - 1;
            }
            return u;
        }

        int e = entry[u], len = length[e];
        int offset = (t - depth[u]) % len;
        return cycle[base[e] + (pos[e] - base[e] + offset) % len];
    };

    vector<pair<int, int>> order(n);
    vector<int> ans(n);

    while (q--) {
        long long t;
        cin >> t;
        for (int i = 0; i < n; ++i) {
            cin >> order[i].first;
            order[i].second = i;
        }
        sort(order.begin(), order.end());

        int mask = 0, previous = 0;
        for (int i = 0; i < n; ) {
            int value = order[i].first;

            // All equal values belong to the same threshold.
            do {
                mask |= 1 << order[i].second;
                ++i;
            } while (i < n && order[i].first == value);

            int now = advance(mask, t);
            for (int bits = now & ~previous; bits; bits &= bits - 1)
                ans[__builtin_ctz(bits)] = value;

            previous = now;
        }

        for (int i = 0; i < n; ++i)
            cout << ans[i] << (i + 1 == n ? '\n' : ' ');
    }
}