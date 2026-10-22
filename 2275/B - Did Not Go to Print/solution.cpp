#include <bits/stdc++.h>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
 
        vector<int> memory;
        vector<bool> printed(n + 1, false);
 
        for (int i = 1; i <= n; ++i) {
            char command = s[i - 1];
 
            if (command == '1') {
                memory.push_back(i);
            } else if (command == '2') {
                if (memory.empty()) {
                    printed[i] = true;
                } else {
                    printed[memory.back()] = true;
                    memory.pop_back();
                }
            } else {
                printed[i] = true;
            }
        }
 
        vector<int> missing;
 
        for (int i = 1; i <= n; ++i) {
            if (!printed[i]) {
                missing.push_back(i);
            }
        }
 
        cout << missing.size() << '
';
 
        for (int i = 0; i < (int)missing.size(); ++i) {
            if (i > 0) cout << ' ';
            cout << missing[i];
        }
 
        cout << '
';
    }
 
    return 0;
}