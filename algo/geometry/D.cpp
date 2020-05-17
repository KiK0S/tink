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
#include <numeric>
#include <ctime>
#include <bitset>
#include <complex>
using namespace std;
 
typedef long long ll;
 
#ifdef DEBUG
    const int MAXN = 10;
#else
    const int MAXN = 5e3 + 100;
#endif
  
const ll INF = 9e18;
 
struct V {
    int x = 0, y = 0;
    int id;
    V() {}
    V(int a, int b) {
        x = a, y = b;
    }
    V(int a, int b, int c) {
        x = a, y = b;
        id = c;
    }
    ll len() {
        return 1ll * x * x + 1ll * y * y;
    }
};
 
struct T {
    V a, b, c;
    T() {}
    T(V _a, V _b, V _c) {
        a = _a, b = _b, c = _c;
    }
};
 
 
int n, m;
V q[MAXN];
  
inline int query(vector<int> &id) {
    cout << "? ";
    cout << id.size() << ' ';
    for (auto it : id) {
        cout << it + 1 << ' ';
    }
    cout << endl;
    string s;
    cin >> s;
    return s[0] == 'Y';
}

inline int query(T t) {
	cout << "? 3 " << t.a.id + 1 << ' ' << t.b.id + 1 << ' ' << t.c.id + 1 << endl;
    string s;
    cin >> s;
    return s[0] == 'Y';
}
 
inline void guess(T t) {
	cout << "! 3 " << t.a.id + 1 << ' ' << t.b.id + 1 << ' ' << t.c.id + 1 << endl;
}

inline void guess(vector<int> &id) {
    cout << "! ";
    cout << id.size() << ' ';
    for (auto it : id) {
        cout << it + 1 << ' ';
    }
    cout << endl;
}
 
inline V operator + (V a, V b) {
    return V(a.x + b.x, a.y + b.y);
}
 
inline V operator - (V a, V b) {
    return V(a.x - b.x, a.y - b.y);
}
 
inline ll operator * (V a, V b) {
    return 1ll * a.x * b.x + 1ll * a.y * b.y;
}
 
inline ll operator ^ (V a, V b) {
    return 1ll * a.x * b.y - 1ll * a.y * b.x;
}
 
bool operator == (V a, V b) {
    return make_pair(a.x, a.y) == make_pair(b.x, b.y);
}
 
bool operator < (V a, V b) {
    return make_pair(-a.x, a.y) < make_pair(-b.x, b.y);
}
 
istream & operator >> (istream &in, V &a) {
    in >> a.x >> a.y;
    return in;
}
 
ostream & operator << (ostream &out, V &a) {
    out << a.id << ' ';
    return out;
}
 
 
inline ll s(V a, V b, V c) {
    return (b - a) ^ (c - a);
}
 
inline ll s(T t) {
    return abs(s(t.a, t.b, t.c));
}
 
inline int in(V O, T t) {
    return s(T(O, t.a, t.b)) + s(T(O, t.a, t.c)) + s(T(O, t.b, t.c)) == s(t);
}
 
 
inline pair<T, T> split(V O, T t) {
	ll A = abs(s(O, t.a, t.b));
	ll B = abs(s(O, t.c, t.b));
	ll C = abs(s(O, t.a, t.c));
	if (A >= B && A >= C) {
		return make_pair(T(O, t.a, t.b), T(t.a, t.b, t.c));
	}
	if (B >= A && B >= C) {
		return make_pair(T(O, t.c, t.b), T(t.c, t.b, t.a));
	}
	if (C >= A && C >= B) {
		return make_pair(T(O, t.a, t.c), T(t.a, t.c, t.b));
	}
}

 
inline bool operator == (T a, T b) {
    return a.a == b.a && a.b == b.b && a.c == b.c;
}
 
T neut;
 
vector<int> inside;
 
inline T minimax(T &t) {
    T tmin;
    ll ans = INF;
    if (inside.empty()) {
    	guess(t);
        return neut;
    }
    int cnt = min((int)inside.size(), (int) 42);
    while (cnt--) {
        int it = rand() % inside.size();
        pair<T, T> spl = split(q[inside[it]], t);
        if (s(spl.first) < ans) {
            tmin = spl.first;
            t = spl.second;
            ans = s(spl.first);
        }
    }
    return tmin;
}
 
 
inline void init() {
 
}
 
inline void solve() {
    init();
    V kek((int)-1e9 + 100, 0);
    vector<int> id(n);
    for (int i = 0; i < n; i++) {
        cin >> q[i];
        q[i].id = i;
        id[i] = i;
        if (q[i] < kek) {
            kek = q[i];
        }
    }
    sort(id.begin(), id.end(), [&] (int a, int b) {
        V A = q[a] - kek;
        V B = q[b] - kek;
        if ((A ^ B) == 0) {
            return A.len() < B.len();
        }
        return (A ^ B) > 0;
    });
    vector<int> st;
    st.push_back(id[0]);
    st.push_back(id[1]);
    for (int i = 2; i < n; i++) {
        while (st.size() > 1 && ((q[st[st.size() - 2]] - q[st.back()]) ^ (q[id[i]] - q[st.back()])) >= 0) {
            st.pop_back();
        }
        st.push_back(id[i]);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        // assert(cnt_guess == i);
        int l = 1;
        int r = (int)st.size() - 1;
        T cur(q[st[0]], q[st[1]], q[st.back()]); 
        while (l + 1 < r) {
        	int mid = (l + r) / 2;
            cout << "? " << mid + 1 << ' ';
            for (int i = 0; i <= mid; i++) {
                cout << st[i] + 1 << ' ';
            }
            cout << endl;
            string s;
            cin >> s;
            if (s[0] == 'Y') {
                r = mid;
            }
            else {
                l = mid;
            }
        }
        cur = T(q[st[0]], q[st[l]], q[st[r]]);
        // assert(query(qr));
        T kek1;
        inside.clear();
        for (int j = 0; j < n; j++) {
            if (j != cur.a.id && j != cur.b.id && j != cur.c.id && in(q[j], cur)) {
                inside.push_back(j);
            }
        }
        while (1) {
            vector<int> tmp;
            for (auto j : inside) {
                if (j != cur.a.id && in(q[j], cur)) {
                    tmp.push_back(j);
                }
            }
            tmp.swap(inside);
            kek1 = minimax(cur);
            if (kek1 == neut) {
                break;
            }
            if (query(kek1)) {
                cur = kek1;
            }
            else {
                T a(kek1.a, kek1.b, cur.c);
                T b(kek1.a, kek1.c, cur.c);
                if (query(a)) {
                    cur = a;
                }
                else {
                    cur = b;
                }
            }
        }
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(0));
    cin >> n;
    solve();
    return 0;
}
