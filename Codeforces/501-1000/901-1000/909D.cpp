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

int INF = 1000000000;
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

const int MAXN = 1000010;
int N;
pii arr[MAXN];
int l[MAXN], r[MAXN];

void reset_tc() {

}

void solve() {
    string str;
    cin >> str;
    N = str.length();
    for (int i = 0; i < N; i++) arr[i + 1] = pii(str[i] - 'a', 1);

    r[0] = 1;
    l[N + 1] = N;
    for (int i = 1; i <= N; i++) {
        l[i] = i - 1;
        r[i] = i + 1;
    }

    for (int i = r[0]; i <= N; i = r[i]) {
        if (r[i] <= N && arr[i].FF == arr[r[i]].FF) {
            arr[i].SS += arr[r[i]].SS;

            int t = r[i];
            r[l[t]] = r[t];
            l[r[t]] = l[t];

            // cout << "deleted " << t << endl;

            i = l[i];
        }
    }

    int ops = 0;
    while (r[0] <= N && r[r[0]] <= N) {
        int g1 = r[0];
        int g2 = l[N + 1];
        for (int i = r[0]; i <= N; i = r[i]) {
            int del = 2;
            if (i == g1 || i == g2) del = 1;
            arr[i].SS = max(0, arr[i].SS - del);

            if (arr[i].SS == 0) {
                r[l[i]] = r[i];
                l[r[i]] = l[i];
                i = l[i];

                // cout << "deleted " << i << endl;
            }
        }

        for (int i = r[0]; i <= N; i = r[i]) {
            if (r[i] <= N && arr[i].FF == arr[r[i]].FF) {
                arr[i].SS += arr[r[i]].SS;

                int t = r[i];
                r[l[t]] = r[t];
                l[r[t]] = l[t];

                i = l[i];
            }
        }

        ops++;
    }

    cout << ops << endl;

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