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

const int MAXN = 0;
int N;
int freq[26];

void reset_tc() {
    for (int i = 0; i < 26; i++) freq[i] = 0;
}

void solve() {
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++) freq[s[i] - 'a']++;

    int distinct = 0;
    int minv = 0;
    for (int i = 0; i < 26; i++) if (freq[i]) {
        distinct++;
        if (freq[i] < freq[minv] || !freq[minv]) minv = i;
    }

    if (freq[minv] == 1) {
        cout << (char) (minv + 'a');
        freq[minv]--;

        int bye = 0;
        while (bye < 26) {
            while (bye < 26 && !freq[bye]) bye++;
            if (bye < 26) {
                for (int j = 0; j < freq[bye]; j++) {
                    cout << (char) (bye + 'a');
                }
                freq[bye] = 0;
            }
        }
    }
    else {
        int hi = 0;
        while (hi < 26 && !freq[hi]) hi++;
        
        cout << (char) (hi + 'a');
        if (freq[hi] - 2 <= s.length() - freq[hi]) {
            cout << (char) (hi + 'a');

            int bye = hi + 1;
            for (int i = 0; i < freq[hi] - 2; i++) {
                while (bye < 26 && !freq[bye]) bye++;
                cout << (char) (bye + 'a');
                freq[bye]--;
                cout << (char) (hi + 'a');
            }
            while (bye < 26) {
                while (bye < 26 && !freq[bye]) bye++;
                if (bye < 26) {
                    for (int j = 0; j < freq[bye]; j++) {
                        cout << (char) (bye + 'a');
                    }
                    freq[bye] = 0;
                }
            }
        }
        else {
            if (distinct > 2) {
                int bye = hi + 1;
                while (bye < 26 && !freq[bye]) bye++;
                cout << (char) (bye + 'a');
                freq[bye]--;

                for (int i = 0; i < freq[hi] - 1; i++) cout << (char) (hi + 'a');

                int dye = bye + 1;
                while (dye < 26 && !freq[dye]) dye++;
                cout << (char) (dye + 'a');
                freq[dye]--;

                while (bye < 26) {
                    while (bye < 26 && !freq[bye]) bye++;
                    if (bye < 26) {
                        for (int j = 0; j < freq[bye]; j++) {
                            cout << (char) (bye + 'a');
                        }
                        freq[bye] = 0;
                    }
                }
            }
            else {
                int bye = hi + 1;
                while (bye < 26 && !freq[bye]) bye++;
                if (bye < 26) for (int j = 0; j < freq[bye]; j++) cout << (char) (bye + 'a');
                for (int j = 0; j < freq[hi] - 1; j++) cout << (char) (hi + 'a');
            }
        }
    }
    cout << endl;
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