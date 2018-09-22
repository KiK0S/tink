#include<bits/stdc++.h>
#define int long long
using namespace std;
 
const int MAXN = 2e5 + 10;
 
int n;
pair<int, int> val[MAXN];
vector<pair<int, int>> q;
int dp[MAXN];
int from[MAXN];
int opt[MAXN];
int ss = 0;
 
inline void init(){
    for(int i = 0; i < MAXN; i++){
        val[i] = {0, 0};
        from[i] = 0;
        opt[i] = 0;
        dp[i] = 0;
    }
    from[0] = -1e9;
    ss = 0;
    q.clear();
}
 
void add(int idx){
    while(1){
        if(ss == 0) break;
        int x = ((opt[ss - 1] ? dp[opt[ss - 1] - 1] : 0ll) - (idx ? dp[idx - 1] : 0ll) + q[idx].first - q[opt[ss - 1]].first - 1)
                / (q[idx].first - q[opt[ss - 1]].first);
        if(x < from[ss - 1]){
            ss--;
            continue;
        }
        from[ss] = x;
        break;
    }
    opt[ss++] = idx;
}
 
int cht(int x){
    int l = 0;
    int r = ss;
    while(l + 1 < r){
        int m = (l + r) >> 1;
        if(from[m] > x){
            r = m;
        }
        else{
            l = m;
        }
    }
    return (opt[l] ? dp[opt[l] - 1] : 0) + q[opt[l]].first * x;
    int ans = 1e18;
    for(int i = 0; i < ss; i++){
        ans = min(ans, (i == 0 ? 0 : dp[opt[i]-1]) + q[opt[i]].first * x);
    }
    return ans;
}
 
void solve(){
    init();
    for(int i = 0; i < n; i++){
        cin >> val[i].first >> val[i].second;
    }
    sort(val, val + n);
    int _h = 0;
    for(int i = n - 1; i >= 0; i--){
        if(_h >= val[i].second){
            continue;
        }
        _h = max(_h, val[i].second);
        q.push_back(val[i]);
    }
 
    for(int i = 0; i < q.size(); i++){
        add(i);
        dp[i] = cht(q[i].second);
    }
    cout << dp[q.size()-1] << '\n';
}
 
 
 
signed main() {
    #ifdef DEBUG
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
 
    #endif // DEBUG
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    while(cin >> n)
        solve();
    return 0;
}