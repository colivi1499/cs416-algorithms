#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    int n,m,p;
    cin >> n >> m >> p;

    Dinic dinic(n+m+p+3);

    rep(i, 1, n+1) {
		dinic.addEdge(0,i,1);
        int k;
		cin >> k;
		rep(j, 0, k) {
			int v;
			cin >> v;
			dinic.addEdge(i,n+v,1);
		}
    }

	vector<int> hasCategory(m+1);


	rep(i, 1, p+1) {
		int l;
		cin >> l;
		rep(j, 0, l) {
			int t;
			cin >> t;
			dinic.addEdge(n+t,n+m+i,1);
			hasCategory[t] = 1;
		}
		int r;
		cin >> r;
		dinic.addEdge(n+m+i,n+m+p+2,r);
	}

	rep(i, 1, m+1) {
		if (hasCategory[i] == 0) {
			dinic.addEdge(n+i,n+m+p+1,1);
		}
	}

	dinic.addEdge(n+m+p+1,n+m+p+2,1e9);

	

    ll maxFlow = dinic.calc(0, n+m+p+2);

	cout << maxFlow << "\n";

    return 0;
}