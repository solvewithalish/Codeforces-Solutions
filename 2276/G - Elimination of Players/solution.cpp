#include <bits/stdc++.h>
using namespace std;
 
constexpr int MOD = 998244353;
constexpr int MAXN = 5000;
 
int fact[MAXN + 1];
 
int addmod(int a, int b) {
    int result = a + b;
    if (result >= MOD) result -= MOD;
    return result;
}
 
int submod(int a, int b) {
    int result = a - b;
    if (result < 0) result += MOD;
    return result;
}
 
void solve() {
    int n;
    cin >> n;
 
    vector<int> a(n);
    for (int r = 1; r < n; ++r) {
        cin >> a[r];
    }
 
    // Blocks are stored from oldest to newest.
    vector<pair<int, int>> blocks;
 
    vector<int> seen(n + 1, 0);
    vector<int> currentG(n + 1, 0);
    vector<int> previousG(n + 1, 0);
 
    int previousF = 0;
    long long answer = 0;
 
    for (int r = 1; r < n; ++r) {
        int protectedPlayer = a[r];
 
        if (!blocks.empty() &&
            blocks.back().first == protectedPlayer) {
            ++blocks.back().second;
        } else {
            blocks.emplace_back(protectedPlayer, 1);
        }
 
        int sumF = 0;
        int sumG = 0;
        int retained = 0;
 
        for (int pos = (int)blocks.size() - 1; pos >= 0; --pos) {
            auto [player, length] = blocks[pos];
 
            if (seen[player] == r) break;
 
            seen[player] = r;
            currentG[player] = sumG;
 
            int termF = 1LL * length * fact[n - 1 - retained] % MOD;
            int termG = 1LL * length * fact[n - 2 - retained] % MOD;
 
            if (retained % 2 == 0) {
                sumF = addmod(sumF, termF);
                sumG = addmod(sumG, termG);
            } else {
                sumF = submod(sumF, termF);
                sumG = submod(sumG, termG);
            }
 
            ++retained;
        }
 
        // Older blocks beyond the first repetition are unnecessary.
        int discard = (int)blocks.size() - retained;
        if (discard > 0) {
            blocks.erase(blocks.begin(), blocks.begin() + discard);
        }
 
        for (int player = 1; player <= n; ++player) {
            int g = (seen[player] == r ? currentG[player] : sumG);
 
            if (player != protectedPlayer) {
                int ways = addmod(fact[n - 1], g);
                ways = submod(ways, previousG[player]);
 
                if (r > 1 && a[r - 1] == player) {
                    ways = addmod(ways, previousF);
                }
 
                answer ^= 1LL * ways * player * r;
            }
 
            previousG[player] = g;
        }
 
        previousF = sumF;
    }
 
    cout << answer << '
';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    fact[0] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }
 
    int t;
    cin >> t;
 
    while (t--) {
        solve();
    }
 
    return 0;
}