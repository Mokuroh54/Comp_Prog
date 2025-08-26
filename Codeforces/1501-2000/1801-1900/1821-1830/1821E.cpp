/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
 (___/  (___/  (___/
I am dum duck

Tooting Bec
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second

#define ll long long
#define ld long double
#define ull unsigned ll

#define endl "\n"
#define EPS 1e-9

#define size(v) (int) v.size()
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
// #define cout cerr

ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<pii> vpii;

#define add(a, b) (((a) + (b)) >= MOD ? (a) + (b) - MOD : (a) + (b))
#define sub(a, b) (((a) - (b)) >= 0 ? (a) - (b) : (a) + MOD - (b))
#define mult(a, b) (((a) * (b)) % MOD)
inline ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 64; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
#define divide(a, b) mult(a, power(b, MOD - 2))

#define maxeq(x, y) x = x > y ? x : y
#define mineq(x, y) x = x < y ? x : y
#define addeq(x, y) x = add(x, y)
#define subeq(x, y) x = sub(x, y)
#define multeq(x, y) x = mult(x, y)
#define diveq(x, y) x = divide(x, y)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;
int N, K;
vector<int> nbs[MAXN];
int sz[MAXN];
ll cost[MAXN];
int rt[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        sz[i] = cost[i] = rt[i] = 0;
    }
}

void DFS(int a) {
    for (int nb : nbs[a]) {
        DFS(nb);
        cost[a] += cost[nb];
        sz[a] += sz[nb];
    }
    cost[a] += sz[a];
    sz[a]++;
}

void solve() {
    cin >> K;
    string str;
    cin >> str;
    N = str.length();
    vector<int> golduck;
    vector<int> nodes;
    for (int i = 0; i < N; i++) {
        if (str[i] == '(') golduck.pb(i + 1);
        else {
            int f = golduck.back();
            // cout << "new node with " << f << " " << i + 1 << endl;
            while (size(nodes) && nodes.back() > f) {
                // cout << "child is " << nodes.back() << endl;
                nbs[f].pb(nodes.back());
                rt[nodes.back()] = 0;
                nodes.ppb();
            }
            rt[f] = 1;
            nodes.pb(f);
            golduck.ppb();
        }
    }

    priority_queue<pii> guys;
    for (int i = 1; i <= N; i++) if (rt[i]) {
        DFS(i);
        guys.push(pii(sz[i], i));
    }

    for (int i = 1; i <= K; i++) if (size(guys)) {
        int n = guys.top().SS;
        guys.pop();

        rt[n] = 0;
        for (int nb : nbs[n]) {
            rt[nb] = 1;
            guys.push(pii(sz[nb], nb));
        }
    }

    ll ans = 0;
    for (int i = 1; i <= N; i++) if (rt[i]) ans += cost[i];
    
    cout << ans << endl;

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 