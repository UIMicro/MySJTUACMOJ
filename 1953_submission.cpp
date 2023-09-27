#include <bits/stdc++.h>
using namespace std;

pair<int, int> partition(vector <int>& a, int pivot) {
    vector<int> lpart, mpart, rpart;
    for (auto i : a) {
        if (i < pivot) lpart.push_back(i);
        else if (i == pivot) mpart.push_back(i);
        else rpart.push_back(i);
    }
    a.clear();
    a.insert(a.end(), lpart.begin(), lpart.end());
    a.insert(a.end(), mpart.begin(), mpart.end());
    a.insert(a.end(), rpart.begin(), rpart.end());
    return { lpart.size(), lpart.size() + mpart.size() };
}

int main() {
    int n, pivot;
    cin >> n >> pivot;
    vector <int> arr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }
    auto [l, r] = partition(arr, pivot);
    for (auto i : arr) cout << i << ' ';
    cout << '\n' << l << ' ' << r << '\n';
}