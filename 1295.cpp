#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    unsigned long long n;
    cin >> n;
    if (n > 1e8) {
        cout << 0;
        return 0;
    }
    bool* isP = new bool[n + 10];
    for (int i = 0; i < n + 9; ++i) {
        isP[i] = true;
    }
    unsigned long long s = 2;
    unsigned long long t;
    int cnt = 1;
    while (s <= n) {
        t = s * 2;
        while (t <= n) {
            isP[t] = false;
            t += s;
        }
        while (!isP[++s]);
        cnt++;
    }
    if (s == n + 1) cnt--;
    double p = cnt / (double)n;
    double q = 2 * p / (double)n;
    cout << fixed << setprecision(15) << q;
    delete[] isP;
    return 0;
}