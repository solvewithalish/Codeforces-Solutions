#include <bits/stdc++.h>
using namespace std;
 
void solve() {
    int n;
    cin >> n;
 
    vector<int> a(n), b(n);
 
    for (int &x : a) cin >> x;
    for (int &x : b) cin >> x;
 
    auto w = [](int x, int y) {
        return (x == y ? 2 : 1);
    };
 
    int cur = w(a[n - 1], b[n - 1]);
 
    for (int i = 0; i < n - 1; i++) {
        cur += w(a[i], b[i + 1]);
        cur += w(a[i + 1], b[i]);
    }
 
    int ans = cur;
 
    for (int i = 0; i < n - 1; i++) {
        cur -= w(a[i], b[i + 1]);
        cur += w(a[i], b[i]);
 
        ans = max(ans, cur);
    }
 
    cout << ans << '
';
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