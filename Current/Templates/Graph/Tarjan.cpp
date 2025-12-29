extern vector<int> nbs[MAXN];

struct Tarjan {
    int T = 0;
    vector<int> t, low, vis;
    vector<int> aps;
    vector<vector<int>> bridges;

    Tarjan(int n) {
        t.resize(n + 1);
        low.resize(n + 1);
        vis.resize(n + 1);
        aps.resize(n + 1);
        bridges.resize(n + 1);
    }

    void calc(int a, int p) {
        if (DFS(a, p) > 1) aps.pb(a);
    }

    int DFS(int a, int p) {
        if (vis[a]) return 0;
        vis[a] = 1;

        t[a] = ++T;
        low[a] = T;

        int subgraphs = 0;
        for (int nb : nbs[a]) if (nb != p) {
            if (!vis[nb]) {
                DFS(nb, a);
                subgraphs++;
                if (t[a] < low[nb]) {
                    bridges[a].pb(nb);
                    bridges[nb].pb(a);
                }
                if (t[a] <= low[nb]) aps[a] = 1;
                low[a] = min(low[a], low[nb]);
            }
            else {
                DFS(nb, a);
                low[a] = min(low[a], t[nb]);
            }
        }

        return subgraphs;
    }
};