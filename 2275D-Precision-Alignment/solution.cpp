#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Lab {
    ll sum;
    ll penalty;
    bool fixed;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        ll k;
        cin >> n >> k;

        vector<Lab> labs(n);
        ll minimumSum = LLONG_MAX;

        for (auto &lab : labs) {
            ll a, b, c;
            cin >> a >> b >> c;

            lab.sum = a + b + c;
            lab.fixed = (a == b && b == c);
            lab.penalty = 0;

            if (!lab.fixed && a <= b && b <= c) {
                ll d = min(b - a, c - b) + 1;
                lab.penalty = 2 * d;
            }

            minimumSum = min(minimumSum, lab.sum);
        }

        auto possible = [&](ll target) {
            ll remaining = k;

            for (const auto &lab : labs) {
                if (lab.sum >= target) {
                    continue;
                }

                if (lab.fixed) {
                    return false;
                }

                ll needed = target - lab.sum + lab.penalty;

                if (needed > remaining) {
                    return false;
                }

                remaining -= needed;
            }

            return true;
        };

        ll low = minimumSum;
        ll high = minimumSum + k;

        while (low < high) {
            ll mid = low + (high - low + 1) / 2;

            if (possible(mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        cout << low << '\n';
    }

    return 0;
}