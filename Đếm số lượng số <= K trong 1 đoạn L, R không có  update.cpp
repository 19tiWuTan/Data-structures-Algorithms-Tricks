/// https://oj.vnoi.info/problem/thswaps
/*
  Mỗi nút IT (l, r) sẽ là 1 cây BIT để quản lý số lượng số <= k
*/
// i'm wutan
#include <bits/stdc++.h>
#define EL cout<<endl
#define el putchar('\n')
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pii pair<int,int>
#define pil pair<int,ll>
#define can(n, q) round(exp(log(n) / q))
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sz(a) int(a.size())
#define FU(x,a,b) for(int x=int(a);x<=int(b);x++)
#define FD(x,a,b) for(int x=int(a);x>=int(b);x--)
#define PROB "thswaps"

using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

// ordered_set name_of_set;
// int pos = *name_of_set.find_by_order(int(value));
*/
typedef long long ll;
typedef double db;


template <typename T>
inline void read(T& x){
    bool Neg = false;
    char c;
    for (c = getchar(); c < '0' | c > '9'; c = getchar())
        if (c == '-') Neg = !Neg;
    x = c - '0';
    for (c = getchar(); c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    if (Neg) x = -x;
}

template <typename T>
inline void write(T x)
{
    if (x < 0)
    {
        putchar('-'); x = -x;
    }
    T p = 1;
    for (T temp = x / 10; temp > 0; temp /= 10) p *= 10;
    for (; p > 0; x %= p, p /= 10) putchar(x / p + '0');
}


void setIO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if(fopen(PROB".inp", "r")){
        freopen(PROB".inp", "r",stdin);
        freopen(PROB".out", "w",stdout);
    }
}

const bool love = true;
const int N = 250003;
const int M = 5e4;
int n, q, a[N];
pii c[N];
vector < vector < int > > b;
vector < vector < int > > st;
ll res = 0;




void build2(int id, int l, int r){
    b[id].pb(M + 1);
    sort(b[id].begin(), b[id].end());
    b[id].resize(unique(b[id].begin(), b[id].end()) - b[id].begin());
    st[id].resize(sz(b[id]) + 2, 0);
    if (l == r) return;
    int mid = (l + r) / 2;
    build2(id * 2, l, mid);
    build2(id * 2 + 1, mid + 1, r);
}

int getpos(int id, int v){
    int p = lower_bound(b[id].begin(), b[id].end(), v) - b[id].begin() + 1;
    if (b[id][p - 1] > v) p--;
    return p;
}

void updbit(int id, int p, int v){
    p = getpos(id, p);
    for (int i = p; i < sz(st[id]); i+= i&-i)
        st[id][i]+= v;
}

int getbit(int id, int p){
    int res = 0;
    p = getpos(id, p);
    for (int i = p; i > 0; i-= i&-i)
        res+= st[id][i];
    return res;
}

void upd (int id, int l, int r, int p, int v, int d){
    if (p < l || p > r) return;
    updbit(id, v, d);
    if (l == r) return;
    int mid = (l + r) / 2;
    upd(id * 2 + 1, mid + 1, r, p, v, d);
    upd(id * 2, l, mid, p, v, d);
}

int get(int id, int l, int r, int u, int v, int L, int R){
    if (r < u || v < l || u > v) return 0;
    if (u <= l && r <= v){
        return getbit(id, R) - getbit(id, L - 1);
    }
    int mid = (l + r) / 2;
    int t1 = get(id * 2, l, mid, u, v, L, R);
    int t2 = get(id * 2 + 1, mid + 1, r, u, v, L, R);

    return t1 + t2;
}

void add (int id, int l, int r, int pos, int val){
    if (pos < l || pos > r) return;
    b[id].pb(val);
    if (l == r) return;
    int mid = (l + r) / 2;
    add(id * 2, l, mid, pos, val);
    add(id * 2 + 1, mid + 1, r, pos, val);
}

void readinp(){
    read(n);
    b.resize(n * 4 + 5); st.resize(n * 4 + 5);
    FU(i, 1, n){
        read(a[i]);
        add(1, 1, n, i, a[i]);
    }
    read(q);
    FU(i, 1, q){
        read(c[i].fi), read(c[i].se);
        add(1, 1, n, c[i].fi, c[i].se);
    }
}

void solve(){
    build2(1, 1, n);
    ll res = 0;
    FU(i, 1, n) upd(1, 1, n, i, a[i], 1);
    FU(i, 1, n - 1) res+= get(1, 1, n, i + 1, n, 1, a[i] - 1);
    FU(i, 1, q){
        int x = c[i].fi;
        int y = c[i].se;

        if (x != 1 && a[x] != M) res-= get(1, 1, n, 1, x - 1,  a[x] + 1, M);
        if (x != n && a[x] != 1) res-= get(1, 1, n, x + 1, n, 1, a[x] - 1);
        upd(1, 1, n, x, a[x], -1);

        a[x] = y;
        upd(1, 1, n, x, a[x], +1);
        if (x != 1 && a[x] != M) res+= get(1, 1, n, 1, x - 1,  a[x] + 1, M);
        if (x != n && a[x] != 1) res+= get(1, 1, n, x + 1, n, 1, a[x] - 1);
        cout << res,EL;
    }
}

int main(){
    setIO();
    int t = 1;
//    cin >> t;
    while (t--){
        readinp();
        solve();
    }
    return 0;
}
