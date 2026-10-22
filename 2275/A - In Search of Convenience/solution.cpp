#include <iostream>
using namespace std;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
 
    while (t--) {
        int x0, y0, R;
        cin >> x0 >> y0 >> R;
 
        cout << x0 + R << ' ' << y0 << '
';
    }
 
    return 0;
}