#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int query(const vector<int>& vertices) {
    cout << "? 1 " << vertices.size();

    for (int v : vertices) {
        cout << " " << v;
    }

    cout << endl;  // Flush output

    int response;
    cin >> response;

    if (response == -1) {
        exit(0);
    }

    return response;
}

// Binary search for the first vertex that
// makes the queried induced graph non-bipartite.
//
// include = vertices always included.
// v       = vertices added progressively.
int binarySearch(
    const vector<int>& v,
    const vector<int>& include
) {
    int lo = 0;
    int hi = (int)v.size();

    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;

        vector<int> ask = include;

        for (int i = 0; i < mid; i++) {
            ask.push_back(v[i]);
        }

        if (query(ask)) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return v[lo];
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Step 1: Find connected components
    // and create a DFS preorder.

    vector<int> comp(n + 1, -1);
    vector<int> dfsOrder;

    int componentCount = 0;

    function<void(int, int)> dfs =
        [&](int u, int cid) {
            comp[u] = cid;
            dfsOrder.push_back(u);

            for (int v : adj[u]) {
                if (comp[v] == -1) {
                    dfs(v, cid);
                }
            }
        };

    for (int i = 1; i <= n; i++) {
        if (comp[i] == -1) {
            dfs(i, componentCount);
            componentCount++;
        }
    }

    // Step 2: Find one hidden-edge endpoint.
    // The first bad prefix identifies vertex a.

    vector<int> empty;

    int a = binarySearch(dfsOrder, empty);

    int targetComponent = comp[a];

    // Step 3: Separate the other components.

    vector<int> outside;

    for (int v : dfsOrder) {
        if (comp[v] != targetComponent) {
            outside.push_back(v);
        }
    }

    // Step 4: DFS inside a's component,
    // starting from a.

    vector<int> inside;
    vector<bool> visited(n + 1, false);

    function<void(int)> dfsInside =
        [&](int u) {
            visited[u] = true;
            inside.push_back(u);

            for (int v : adj[u]) {
                if (!visited[v]) {
                    dfsInside(v);
                }
            }
        };

    dfsInside(a);

    // Step 5: Find the second endpoint
    // inside a's component.

    int b = binarySearch(inside, outside);

    // Step 6: Find the second endpoint
    // in the other component.

    int c = binarySearch(outside, inside);

    // Step 7: Check whether (a,c) is hidden.

    cout << "? 2 " << a << " " << c << endl;

    int response;
    cin >> response;

    if (response == -1) {
        exit(0);
    }

    // Step 8: Report one hidden edge.

    if (response == 1) {
        cout << "! " << a << " " << c << endl;
    } else {
        cout << "! " << b << " " << c << endl;
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
