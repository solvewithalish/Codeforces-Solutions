#include <bits/stdc++.h>
using namespace std;

// Returns the first and last uncovered indices.
// {-1, -1} means the array is already beautiful.
pair<int, int> uncovered(const vector<int>& a) {
    int n = (int)a.size();

    vector<int> st;
    vector<int> diff(n + 1, 0);
    st.reserve(n);

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] < a[i]) {
            st.pop_back();
        }

        if (!st.empty() && a[st.back()] == a[i]) {
            int left = st.back();
            st.pop_back();

            ++diff[left];
            --diff[i + 1];
        }

        st.push_back(i);
    }

    int first = -1, last = -1;
    int coverage = 0;

    for (int i = 0; i < n; ++i) {
        coverage += diff[i];

        if (coverage == 0) {
            if (first == -1) first = i;
            last = i;
        }
    }

    return {first, last};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<int> a(n);
        for (int& x : a) cin >> x;

        auto [L, R] = uncovered(a);

        if (L == -1) {
            cout << 0 << '\n';
            continue;
        }

        vector<pair<int, int>> candidates;

        if (L + 1 < n) {
            int value = *max_element(a.begin() + L + 1, a.end());
            candidates.push_back({L, value});
        }

        if (R > 0) {
            int value = *max_element(a.begin(), a.begin() + R);
            candidates.push_back({R, value});
        }

        int position = max_element(
            a.begin() + L, a.begin() + R + 1
        ) - a.begin();

        candidates.push_back({position, 1});

        bool found = false;

        for (auto [index, value] : candidates) {
            int original = a[index];
            a[index] = value;

            bool beautiful = (uncovered(a).first == -1);

            a[index] = original;

            if (beautiful) {
                cout << 1 << '\n';
                cout << index + 1 << ' ' << value << '\n';
                found = true;
                break;
            }
        }

        if (found) continue;

        int maximum = *max_element(a.begin(), a.end());

        vector<pair<int, int>> operations;

        if (a.front() != maximum) {
            operations.push_back({1, maximum});
        }

        if (a.back() != maximum) {
            operations.push_back({n, maximum});
        }

        cout << operations.size() << '\n';

        for (auto [index, value] : operations) {
            cout << index << ' ' << value << '\n';
        }
    }

    return 0;
}