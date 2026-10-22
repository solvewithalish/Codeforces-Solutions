#include <bits/stdc++.h>
using namespace std;
 
bool aliceWins(int n, int k, const vector<int>& p) {
    vector<bool> visited(n, false);
    vector<int> cycles;
 
    for (int i = 0; i < n; ++i) {
        if (visited[i]) continue;
 
        int length = 0;
        int v = i;
 
        while (!visited[v]) {
            visited[v] = true;
            ++length;
            v = p[v];
        }
 
        cycles.push_back(length);
    }
 
    sort(cycles.rbegin(), cycles.rend());
 
    if (k == 1) {
        if (cycles[0] >= 3) return false;
        return cycles[0] == 1 || n % 2 == 1;
    }
 
    if (cycles[0] > k + 1) {
        return false;
    }
 
    if (cycles[0] == k + 1) {
        if (cycles.size() > 1 && cycles[1] == k + 1) {
            return false;
        }
 
        int required = 0;
        int singletons = 0;
 
        for (int i = 1; i < (int)cycles.size(); ++i) {
            if (cycles[i] == 1) {
                ++singletons;
            } else {
                required += cycles[i];
            }
        }
 
        required += singletons % (k + 1);
        return required >= 1 && required <= k;
    }
 
    // All cycles have length at most k.
    // Only the largest 2*k cycles can affect the decision.
    int m = min((int)cycles.size(), 2 * k);
    const int INF = 1e9;
 
    // dp[used][removed]:
    // Minimum forced repair cost after processing some cycles,
    // where Alice spends 'used' elements to finish 'removed' cycles.
    vector<vector<int>> dp(k + 1, vector<int>(k + 1, INF));
    dp[0][0] = 0;
 
    for (int i = 0; i < m; ++i) {
        vector<vector<int>> next(k + 1, vector<int>(k + 1, INF));
 
        for (int used = 0; used <= k; ++used) {
            for (int removed = 0; removed <= k; ++removed) {
                if (dp[used][removed] == INF) continue;
 
                int cost = dp[used][removed];
 
                // Alice finishes this cycle on her first turn.
                if (used + cycles[i] <= k && removed < k) {
                    int& destination =
                        next[used + cycles[i]][removed + 1];
 
                    destination = min(destination, cost);
                }
 
                // Leave this cycle for later.
                // Bob can start up to k remaining cycles.
                int extra = 0;
                if (i - removed < k) {
                    extra = cycles[i] - 1;
                }
 
                next[used][removed] =
                    min(next[used][removed], cost + extra);
            }
        }
 
        dp.swap(next);
    }
 
    for (int used = 0; used <= k; ++used) {
        for (int removed = 0; removed <= k; ++removed) {
            if (dp[used][removed] <= k) {
                return true;
            }
        }
    }
 
    return false;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n, k;
        cin >> n >> k;
 
        vector<int> p(n);
        for (int& value : p) {
            cin >> value;
            --value;
        }
 
        cout << (aliceWins(n, k, p) ? "Alice" : "Bob") << '
';
    }
 
    return 0;
}