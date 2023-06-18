#include <iostream>
#include <iomanip>

using namespace std;

void qksort(int arr[], int l, int r) {
    if (l < r) {
        int i = l, j = r, mid = arr[l];
        while (i < j) {
            while (i < j && arr[j] >= mid) {
                j--;
            }
            if (i < j) {
                arr[i++] = arr[j];
            }
            while (i < j && arr[i] < mid) {
                i++;
            }
            if (i < j) {
                arr[j--] = arr[i];
            }
        }
        arr[i] = mid;
        qksort(arr, l, i - 1);
        qksort(arr, i + 1, r);
    }
}

int main()
{
    int n, m;
    cin >> n;
    int* li = new int[n];
    for (int t = 0; t < n; ++t) cin >> li[t];
    cin >> m;
    int* boy = new int[m];
    int* girl = new int[m];
    int boycnt = 0;
    int girlcnt = 0;
    int lab;
    for (int t = 0; t < m; ++t) {
        cin >> lab;
        if (lab == 1) {
            cin >> boy[boycnt++];
        }
        else {
            cin >> girl[girlcnt++];
        }
    }
    qksort(boy, 0, boycnt - 1);
    qksort(girl, 0, girlcnt - 1);
    long long boywait = 0, girlwait = 0;
    int boyi = 0, girli = 0;
    long long time = 0;
    while (boyi < boycnt && boy[boyi] == 0 && girli < girlcnt && girl[girli] == 0) {
        boyi++;
        girli++;
    }
    int i;
    for (i = 0; i < n - 2; ++i) {
        while (boyi < boycnt && boy[boyi] <= time + li[i] && girli < girlcnt && girl[girli] <= time + li[i]) {
            boywait += (time + li[i] - boy[boyi]);
            girlwait += (time + li[i] - girl[girli]);
            boyi++;
            girli++;
        }
        time += li[i];
    }
    while (boyi < boycnt) {
        boywait += (time + li[i] - boy[boyi]);
        boyi++;
    }
    while (girli < girlcnt) {
        girlwait += (time + li[i] - girl[girli]);
        girli++;
    }
    if (boycnt == 0) {
        cout << "0.00";
    }
    else {
        cout << fixed << setprecision(2) << (double)boywait / boycnt;
    }
    cout << ' ';
    if (girlcnt == 0) {
        cout << "0.00";
    }
    else {
        cout << fixed << setprecision(2) << (double)girlwait / girlcnt;
    }
    delete[] li;
    delete[] boy;
    delete[] girl;
}