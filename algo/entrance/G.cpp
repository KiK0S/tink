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
    const int MAXN = 10;
#else
    const int MAXN = 101;
#endif
 
int n, m;
int g[MAXN][MAXN];
 
inline void init() {
    memset(g, 0, sizeof(g));
}
 
inline void solve() {
    init();
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a][b] = 1;
        g[b][a] = 1;
    }
    for (int i = 0; i < n; i++) {
        g[i][i] = 1;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][k] && g[k][j]) {
                    g[i][j] = 1;
                }
            }
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        if (g[a][b] == 1) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (g[a][j]) {
                    sum++;
                }
            }
            cout << sum << '\n';
        }
        else {
            cout << 0 << '\n';
        }
    }
}
 
signed main() {
    #ifdef DEBUG
        freopen("floyd.in", "r", stdin);
        freopen("floyd.out", "w", stdout);
    #else
   
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> m)
        solve();
    return 0;
}