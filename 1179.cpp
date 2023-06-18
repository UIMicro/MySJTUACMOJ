#include <iostream>
#include <algorithm>

using namespace std;

struct mouse {
    int score;
    int pow;
    int id;
    mouse() { score = 0; pow = 0; id = 0; }
};

bool operator<(const mouse m1, const mouse m2) {
    if (m1.score == m2.score) return m1.id < m2.id;
    else return m1.score > m2.score;
}

struct Range {
    int start, end;
    Range(int s = 0, int e = 0) { start = s; end = e; }
};

void qksort(mouse arr[], const int len) {
    if (len <= 0) return;
    Range* r = new Range[len];
    int p = 0;
    r[p++] = Range(0, len - 1);
    while (p) {
        Range range = r[--p];
        if (range.start >= range.end) continue;
        mouse mid = arr[range.end];
        int left = range.start, right = range.end - 1;
        while (left < right) {
            while (arr[left] < mid && left < right) left++;
            while (!(arr[right] < mid) && left < right) right--;
            swap(arr[left], arr[right]);
        }
        if (!(arr[left] < arr[range.end]))
            std::swap(arr[left], arr[range.end]);
        else
            left++;
        r[p++] = Range(range.start, left - 1);
        r[p++] = Range(left + 1, range.end);
    }
    delete[] r;
}

int main() {
    ios::sync_with_stdio(false);
    int n, r;
    cin >> n >> r;
    mouse* m = new mouse[n * 2];
    for (int i = 0; i < n * 2; ++i) {
        cin >> m[i].score;
        m[i].id = i + 1;
    }
    for (int i = 0; i < n * 2; ++i) {
        cin >> m[i].pow;
    }
    //qksort(m, 0, n * 2 - 1);
    qksort(m, n * 2);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < n; ++j) {
            if (m[j * 2].pow < m[j * 2 + 1].pow) {
                m[j * 2 + 1].score += 2;
                continue;
            }
            if (m[j * 2].pow > m[j * 2 + 1].pow) {
                m[j * 2].score += 2;
                continue;
            }
            if (m[j * 2].pow == m[j * 2 + 1].pow) {
                m[j * 2 + 1].score += 1;
                m[j * 2].score += 1;
                continue;
            }
        }
        //qksort(m, 0, n * 2 - 1);
        qksort(m, n * 2);
    }
    for (int i = 0; i < n * 2; ++i) {
        cout << m[i].id << ' ';
    }
    delete[] m;
}