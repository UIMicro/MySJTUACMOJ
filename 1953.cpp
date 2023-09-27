#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
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
    return { lpart.size(), lpart.size() + mpart.size()};
}

int main() {
    int n, pivot;
    cin >> n >> pivot;
    vector <int> arr, before;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        arr.push_back(x);
    }
    before = arr;
    auto [l, r] = partition(arr, pivot);
    cout << "Returns: " << l << " " << r << endl;
    cout << "Array after modification:";
    for (auto i : arr) {
        cout << ' ' << i;
    }
    cout << endl;
    // check solution:
    vector <int> after = arr;
    sort(before.begin(), before.end());
    sort(after.begin(), after.end());
    if (before != after) {
        cout << "FAILED: numbers not matched" << endl;
        return 1;
    }
    if (l < 0 || r > n || l > r || (l == r && (l == 0 || l == n))) {
        cout << "FAILED: l r at bad position" << endl;
        return 1;
    }
    int left = 0, right = 0, mid = 0;
    for (int i = 0; i < l; i++) {
        if (arr[i] > pivot) {
            cout << "FAILED: position " << i << " is greater than pivot" << endl;
            return 1;
        }
        if (arr[i] == pivot) left++;
    }
    for (int i = l; i < r; i++) {
        if (arr[i] != pivot) {
            cout << "FAILED: position " << i << " is not equal to pivot" << endl;
            return 1;
        }
        mid++;
    }
    for (int i = r; i < n; i++) {
        if (arr[i] < pivot) {
            cout << "FAILED: position " << i << " is less than pivot" << endl;
            return 1;
        }
        if (arr[i] == pivot) right++;
    }
    double ratio = max(left, right) * 1. / (left + mid + right);
    cout << "Ratio: " << ratio << endl;
    if (max(left, right) > 10 && ratio > 0.8) {
        cout << "FAILED: too imbalanced" << endl;
        return 1;
    }
    cout << "OK" << endl;
}