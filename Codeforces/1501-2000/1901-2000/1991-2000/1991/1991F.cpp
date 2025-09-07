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

const int MAXN = 100010;
int N, Q;
int arr[MAXN];

void reset_tc() {

}

void solve() {
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= Q; i++) {
        int l, r;
        cin >> l >> r;
        if (r - l >= 50) cout << "YES" << endl;
        else {
            vector<int> guys;
            for (int j = l; j <= r; j++) guys.pb(arr[j]);
            sort(guys.begin(), guys.end());

            int yay = 0;
            for (int j = 0; j < size(guys) - 5; j++) { 
                for (int a = 0; a < 6; a++) {
                    for (int b = a + 1; b < 6; b++) {
                        for (int c = b + 1; c < 6; c++) if (guys[j + a] + guys[j + b] > guys[j + c]) {
                            vector<int> rem;
                            for (int k = 0; k < 6; k++) if (k != a && k != b && k != c) rem.pb(k);

                            if (guys[j + rem[0]] + guys[j + rem[1]] > guys[j + rem[2]]) {
                                yay = 1;
                                break;
                            }
                        }
                        if (yay) break;
                    }
                    if (yay) break;
                }
                if (yay) break;
            }

            int friends = 0;
            for (int j = 2; j < size(guys); j++) { 
                if (guys[j - 2] + guys[j - 1] > guys[j]) {
                    friends++;
                    j += 2;
                }
            }
            
            if (yay || friends >= 2) cout << "YES" << endl;
            else cout << "NO" << endl;
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