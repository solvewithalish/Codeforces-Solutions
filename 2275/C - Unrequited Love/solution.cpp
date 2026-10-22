#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    constexpr int OFFSET = 30000;
    constexpr int RANGE = 60001;
 
    vector<int> frequency(RANGE, 0);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n;
        cin >> n;
 
        vector<int> a(n);
        for (int& x : a) cin >> x;
 
        int count = n - 4;
        vector<int> value(count);
 
        long long answer = 0;
 
        for (int i = 0; i < count; ++i) {
            value[i] = a[i] + a[i + 2] - a[i + 4];
 
            int id = value[i] + OFFSET;
 
            answer += frequency[id];
 
            if (i >= 2 && value[i] == value[i - 2]) {
                --answer;
            }
 
            if (i >= 4 && value[i] == value[i - 4]) {
                --answer;
            }
 
            ++frequency[id];
        }
 
        cout << answer << '
';
 
        // Reset only values used in this test case.
        for (int x : value) {
            frequency[x + OFFSET] = 0;
        }
    }
 
    return 0;
}