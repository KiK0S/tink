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
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <ctime>
#include <bitset>
using namespace std;
 
typedef long long ll;
 
#ifdef DEBUG
    const int MAXN = 2e5 + 10;
#else
    const int MAXN = 4e5 + 10;
#endif
 
#define int ll
 
int n, m;
ll ans[MAXN];
vector<int> g[MAXN];
vector<int> pre[MAXN];
int fup[MAXN];
int tin[MAXN];
int timer;
int used[MAXN];
int point[MAXN];
vector<int> all[MAXN];
vector<int> good[MAXN];
 
inline void init() {
    for (int i = 0; i < MAXN; i++) {
        ans[i] = n - 1;
        used[i] = 0;
        point[i] = 0;
        g[i].clear();
        all[i].clear();
        pre[i].clear();
    }
    timer = 0;
}
 
void find(int v, int p = -1) {
    used[v] = 1;
    tin[v] = timer++;
    fup[v] = tin[v];
    pre[v].push_back(timer);
    int cnt = 0;
    for (auto to : g[v]) {
        if (to == p) {
            continue;
        }
        if (used[to]) {
            fup[v] = min(fup[v], tin[to]);
        }
        else {
            cnt++;
            find(to, v);
            all[v].push_back(timer - pre[v].back());
            pre[v].push_back(timer);
            fup[v] = min(fup[v], fup[to]);
            if (p != -1 && fup[to] >= tin[v]) {
                point[v] = 1;      
                good[v].push_back(all[v].back());
            }
            if (p == -1) {
                good[v].push_back(all[v].back());
            }
        }
    }
    if (p == -1 && cnt > 1) {
        point[v] = 1;
    }
    if (point[v]) {
        ans[v] <<= 1;
        int sum = 0;
        for (auto it : good[v]) {
            sum += it;
        }
        good[v].push_back(n - sum - 1);
        for (auto it : good[v]) {
            ans[v] += (n - 1 - it) * it;
        }
        ans[v] >>= 1;
    }
}
 
inline void solve() {
    init();
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }  
    find(0);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << '\n';
    }
}
 
signed main() {
    #ifdef DEBUG
        freopen("K.in", "r", stdin);
        freopen("K.out", "w", stdout);
    #else
   
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> m)
        solve();
    return 0;
}
