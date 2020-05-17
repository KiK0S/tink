#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <numeric>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <ctime>
#include <bitset>
#include <complex>
using namespace std;
 
typedef long long ll;
 
#ifdef DEBUG
    const int MAXN = 10;
#else
    const int MAXN = 1e5 + 10;
#endif
// #define int ll
int n;
 
ll val[MAXN];
#define plus PLUS
#define minus MINUS
vector<int> plus(MAXN);
vector<int> minus(MAXN);
 
struct segtree {
    vector<int> all;
    vector<ll> pref;
};
 
vector<segtree> a(4 * MAXN), b(4 * MAXN);
 
inline void build(int v, int tl, int tr, vector<segtree> &t, vector<int> &vl) {
    if (tl == tr) {
        t[v].all.clear();
        t[v].pref.clear();
        // assert(vl[tl] >= -5000);
        t[v].all.push_back(vl[tl]);
        t[v].pref.push_back(vl[tl]);
        return;
    }
    int tm = (tl + tr) >> 1;
    build(2 * v, tl, tm, t, vl);
    build(2 * v + 1, tm + 1, tr, t, vl);
    t[v].all.resize(t[2 * v].all.size() + t[2 * v + 1].all.size());
    t[v].pref.resize(t[v].all.size());
    merge(t[2 * v].all.begin(), t[2 * v].all.end(), t[2 * v + 1].all.begin(), t[2 * v + 1].all.end(), t[v].all.begin());
    for (int i = 0; i < t[v].all.size(); i++) {
        t[v].pref[i] = (i == 0 ? 0 : t[v].pref[i - 1]) + t[v].all[i];
    }
    // partial_sum(t[v].all.begin(), t[v].all.end(), t[v].pref.begin());
}
 
inline ll get(int v, int tl, int tr, vector<segtree> &t, int l, int r, ll x) {
    if (tl > r || l > tr) {
        return 0;
    }
    if (l <= tl && tr <= r) {
        int pos = lower_bound(t[v].all.begin(), t[v].all.end(), x) - t[v].all.begin();
        ll ret = 0;
        if (pos) {
            ret += pos * x - t[v].pref[pos - 1];
        }
        ret += t[v].pref.back() - (pos == 0 ? 0ll : t[v].pref[pos - 1]) - (t[v].all.size() - pos) * x;
        return ret;
    }
    int tm = (tl + tr) >> 1;
    return get(2 * v, tl, tm, t, l, r, x) + get(2 * v + 1, tm + 1, tr, t, l, r, x);
}
 
ll res = 1e18;
// pair<int, ll> used[MAXN];
// int used[MAXN];
 
ll check(int pos, int rc) {
    if (rc - max(pos, n - 1 - pos) <= 0) {
        return 1e18;
    }
    ll prc = rc + pos;
    ll mrc = rc - pos;
    ll ans = get(1, 0, n - 1, a, pos, n - 1, prc) + get(1, 0, n - 1, b, 0, pos - 1, mrc);
    res = min(res, ans);
    // cerr << ans << '\n';
    return ans;
}
 
inline void init() {
    res = 1e18;
}
 
inline void solve() {
    init();
    srand(time(0));
    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        total += val[i];
        plus[i] = val[i] + i;
        minus[i] = val[i] - i;
    }
    int cursum = 0;
    int bestid = -1;
    for (int i = 0; i < n; i++) {
        cursum += val[i];
        if (cursum * 2 <= total) {
            bestid = i;
        }
    }
    build(1, 0, n - 1, a, plus);
    build(1, 0, n - 1, b, minus);
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
    	idx[i] = i;
    }
    random_shuffle(idx.begin(), idx.end());
    for (auto c : idx) {
        // if (clock() * 1.0 / CLOCKS_PER_SEC > 1.45) {
        //     break;
        // }
        int l = 1;
        int r = 1e9 + 1e5;
        while (l + 2 < r) {
            int mid = (l + r) >> 1;
            if (check(c, mid) < check(c, mid + 1)) {
                r = mid + 1;
            }
            else {
                l = mid;
            }
        }
    }
    assert(res >= 0);
    cout << res << '\n';
}
 
signed main() {
    #ifdef DEBUG
        freopen("D.in", "r", stdin);
        freopen("D.out", "w", stdout);
    #else
   
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n)
        solve();
    return 0;
}
