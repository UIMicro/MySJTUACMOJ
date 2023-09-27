// This is a qsort-like implementation. If I have time I can try heap sort.
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <utility>

using namespace std;

// use precise time as random seed
const int RANDOM_SEED = chrono::system_clock::now().time_since_epoch().count();
mt19937 rng(RANDOM_SEED); // random number generator

inline int randint(int l, int r) { // rand in [l, r]
    return int(rng() % (r - l + 1) + l);
}

int n, k;
vector <int> a;
void read_input_data_vector()
{
    int m;
    cin >> n >> k >> m; a.resize(n);
    for (int i = 0; i < m; i++)
    {
        cin >> a[i];
    }
    unsigned int z = a[m - 1];
    for (int i = m; i < n; i++)
    {
        z ^= z << 13;
        z ^= z >> 17;
        z ^= z << 5;
        a[i] = z & 0x7fffffff;
    }
}

inline pair<int, int> partition(vector<int>::iterator l, vector<int>::iterator r, int pivot) {
    vector<int> lpart, mpart, rpart;
    for (auto i = l; i < r; ++i) {
        if (*i < pivot) lpart.push_back(*i);
        else if (*i == pivot) mpart.push_back(*i);
        else rpart.push_back(*i);
    }
    auto i = l;
    for (auto j : lpart) {
        *(i++) = j;
    }
    for (auto j : mpart) {
        *(i++) = j;
    }
    for (auto j : rpart) {
        *(i++) = j;
    }
    return { lpart.size(), lpart.size() + mpart.size() };
}

int find_3p(vector<int>::iterator l, vector<int>::iterator r, int k) {
    if (l == r) return *l;
    auto [lsize, msize] = partition(l, r, *(l + randint(0, r - l - 1))); //partition with randomly chosen pivot to avoid complexity regression(is it the correct word?)
    if (k <= lsize) return find_3p(l, l + lsize, k);
    else if (k <= msize) return *(l + k - 1);
    else return find_3p(l + msize, r, k - msize);
}

int main() {
    read_input_data_vector();
    cout << find_3p(a.begin(), a.end(), k);
    return 0;
}