struct Edge{
    ll flow;
    ll cap;
    int s, d;
    int res;
};

extern vector<Edge> edges;
extern vector<int> nbs[MAXN];

struct Dinic {
    vector<int> vis;
    vector<int> level;
    vector<int> ptr;
    int s, t, n;

    Dinic(int tn, int ts, int tt) {
        vis.resize(tn + 1);
        level.resize(tn + 1);
        ptr.resize(tn + 1);
        s = ts, t = tt, n = tn;

    }

    int BFS() {
        for (int i = 1; i <= n; i++) level[i] = INF, vis[i] = 0, ptr[i] = 0;
        level[s] = 0;
        queue<int> search;
        search.push(s);
        int reached = 0;
        while (!search.empty()) {
            int n = search.front();
            search.pop();

            if (vis[n]) continue;
            vis[n] = 1;
            if (n == t) reached = 1;

            for (int nb : nbs[n]) if (edges[nb].flow < edges[nb].cap) {
                level[edges[nb].d] = min(level[edges[nb].d], level[n] + 1);
                search.push(edges[nb].d);
            }
        }
        return reached;
    }

    ll DFS(vector<int>& path, int a) {
        for (int i = ptr[a]; i < size(nbs[a]); i++) {
            int nb = nbs[a][i];
            if (level[edges[nb].d] == level[a] + 1 && 
                edges[nb].flow < edges[nb].cap) {
                path.pb(nb);
                ll v = DFS(path, edges[nb].d);
                if (edges[nb].d == t) return edges[nb].cap - edges[nb].flow;
                if (v != LINF) return min(v, edges[nb].cap - edges[nb].flow);
                else {
                    ptr[a]++;
                    path.ppb();
                }
            }
        }
        return LINF;
    }

    ll max_flow() {
        ll flow = 0;
        while (BFS()) {
            while (1) {
                vector<int> path;
                ll d = DFS(path, s);
                if (d != LINF) {
                    flow += d;
                    for (int e : path) {
                        edges[e].flow += d;
                        edges[edges[e].res].flow -= d;
                    }
                }
                else break;
            }
        }
        return flow;
    }
};