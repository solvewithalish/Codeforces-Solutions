#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        auto possible = [&](int k) {
            long long capacity = 0;

            for (int size = 1; size <= k; ++size) {
                capacity += 1LL * size * (k / size);

                if (capacity >= n) {
                    return true;
                }
            }

            return false;
        };

        int low = 1, high = n;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (possible(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }

        int k = low;
        cout << k << '\n';

        vector<int> answer;
        answer.reserve(n);

        int remaining = n;
        int bag = 1;

        for (int size = k; size >= 1; --size) {
            int count = min(k / size, remaining / size);

            for (int j = 0; j < count; ++j) {
                for (int x = 0; x < size; ++x) {
                    answer.push_back(bag);
                }
                ++bag;
            }

            remaining -= count * size;
        }

        for (int i = 0; i < n; ++i) {
            cout << answer[i] << (i + 1 == n ? '\n' : ' ');
        }
    }

    return 0;
}