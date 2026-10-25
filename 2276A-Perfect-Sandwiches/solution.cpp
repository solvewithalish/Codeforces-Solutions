#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        long long a, b;
        cin >> a >> b;

        if (a <= b || b == 0) {
            cout << -1 << '\n';
        } else {
            cout << min(b, a - b) << '\n';
        }
    }

    return 0;
}