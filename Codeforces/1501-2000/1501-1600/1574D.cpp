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
int N, M;
vector<int> ducks[11];
ll value(const vector<int>& v) {
    ll s = 0;
    for (int i = 0; i < size(v); i++) s += ducks[i + 1][v[i] - 1];
    return s;
}

struct Comp {
    bool operator()(const vector<int>& v1, const vector<int>& v2) const {
        ll s1 = value(v1);
        ll s2 = value(v2);
        return (s1 == s2 ? v1 > v2 : s1 > s2);
    }
};

void reset_tc() {

}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int ni;
        cin >> ni;
        for (int j = 1; j <= ni; j++) {
            int n;
            cin >> n;
            ducks[i].pb(n);
        }
    }
    set<vector<int>, Comp> bans;
    cin >> M;
    for (int i = 1; i <= M; i++) {
        vector<int> tmp;
        for (int j = 1; j <= N; j++) {
            int n;
            cin >> n;
            tmp.pb(n);
        }
        bans.insert(tmp);
    }

    set<vector<int>, Comp> guys;
    vector<int> max_guy;
    for (int i = 1; i <= N; i++) max_guy.pb(size(ducks[i]));
    guys.insert(max_guy);

    while (!guys.empty()) {
        vector<int> duck = *guys.begin();
        guys.erase(guys.begin());

        if (!bans.count(duck)) {
            for (int n : duck) cout << n << " ";
            cout << endl;
            return;
        }

        for (int i = 0; i < N; i++) {
            if (duck[i] > 1) {
                duck[i]--;
                guys.insert(duck);
                duck[i]++;
            }
        }
    }

    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    T = 1;
    // cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 