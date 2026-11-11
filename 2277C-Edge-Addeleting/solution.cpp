#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> graph(n + 1);

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> dist(n + 1, -1);
        vector<int> order;
        order.reserve(n);

        dist[n] = 0;
        order.push_back(n);

        int answer = 0;

        // Traverse n's component without entering vertex 1.
        for (int i = 0; i < (int)order.size(); ++i) {
            int u = order[i];

            for (int v : graph[u]) {
                if (v == 1) {
                    answer = dist[u] + 1;
                    continue;
                }

                if (dist[v] != -1) continue;

                dist[v] = dist[u] + 1;
                order.push_back(v);
            }
        }

        for (int i = 0; i < m; ++i) {
            int v;
            cin >> v;

            if (dist[v] != -1) {
                answer = max(answer, dist[v] + 1);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}