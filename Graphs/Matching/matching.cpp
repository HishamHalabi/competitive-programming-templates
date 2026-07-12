#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const long long LL_INF = 1e18;

// =========================================================================
// 1. UNWEIGHTED BIPARTITE ENGINE (Hopcroft-Karp) -> Time: O(E * sqrt(V))
//    1-BASED INDEXING SUPPORTED: Node tags must span [1, n]
// =========================================================================
struct BipartiteBlackBox {
    int n, left_sz = 0, right_sz = 0;
    vector<vector<int>> orig_adj, adj;
    vector<int> color, id, left_nodes, right_nodes, pair_u, pair_v, dist;
    vector<bool> vis_u, vis_v;

    // Allocate size up to (n + 1) to naturally accommodate 1-based indices
    BipartiteBlackBox(int n) : n(n), orig_adj(n + 1), color(n + 1, -1), id(n + 1, -1) {}

    // Use for Max Matching, Vertex Cover, and Independent Set
    void add_undirected_edge(int u, int v) { orig_adj[u].push_back(v); orig_adj[v].push_back(u); }

    // Use strictly for DAG Path Cover problems
    void add_directed_edge(int u, int v) { orig_adj[u].push_back(v); }

    bool split() {
        for (int i = 1; i <= n; i++) {
            if (color[i] != -1) continue;
            queue<int> q; q.push(i); color[i] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v : orig_adj[u]) {
                    if (color[v] == -1) { color[v] = 1 - color[u]; q.push(v); }
                    else if (color[v] == color[u]) return false; 
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            if (color[i] == 0) { id[i] = left_sz++; left_nodes.push_back(i); }
            else { id[i] = right_sz++; right_nodes.push_back(i); }
        }
        adj.resize(left_sz); pair_u.assign(left_sz, -1); pair_v.assign(right_sz, -1); dist.resize(left_sz);
        for (int u : left_nodes)
            for (int v : orig_adj[u]) if (color[v] == 1) adj[id[u]].push_back(id[v]);
        return true;
    }

    bool bfs() {
        queue<int> q; int min_d = INF;
        for (int u = 0; u < left_sz; u++) {
            if (pair_u[u] == -1) { dist[u] = 0; q.push(u); }
            else dist[u] = INF;
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] < min_d) {
                for (int v : adj[u]) {
                    if (pair_v[v] == -1) min_d = dist[u] + 1;
                    else if (dist[pair_v[v]] == INF) { dist[pair_v[v]] = dist[u] + 1; q.push(pair_v[v]); }
                }
            }
        }
        return min_d != INF;
    }

    bool dfs(int u) {
        for (int v : adj[u]) {
            if (pair_v[v] == -1 || dist[pair_v[v]] == dist[u] + 1) {
                if (pair_v[v] == -1 || dfs(pair_v[v])) { pair_u[u] = v; pair_v[v] = u; return true; }
            }
        }
        dist[u] = INF; return false;
    }

    // 1. Max Pairs chosen with no shared nodes
    int solve_max_matching() {
        if (!split()) return -1;
        int res = 0;
        while (bfs()) for (int u = 0; u < left_sz; u++) if (pair_u[u] == -1 && dfs(u)) res++;
        return res;
    }

    // 2. Min nodes to touch every edge (Returns 1 for chosen nodes using 1-based indexing)
    vector<int> solve_minimum_vertex_cover() {
        if (solve_max_matching() == -1) return {};
        vis_u.assign(left_sz, false); vis_v.assign(right_sz, false); queue<int> q;
        for (int u = 0; u < left_sz; u++) if (pair_u[u] == -1) { q.push(u); vis_u[u] = true; }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (!vis_v[v]) {
                    vis_v[v] = true; int nxt = pair_v[v];
                    if (nxt != -1 && !vis_u[nxt]) { vis_u[nxt] = true; q.push(nxt); }
                }
            }
        }
        vector<int> cover(n + 1, 0);
        for (int i = 0; i < left_sz; i++) if (!vis_u[i]) cover[left_nodes[i]] = 1;
        for (int j = 0; j < right_sz; j++) if (vis_v[j]) cover[right_nodes[j]] = 1;
        return cover;
    }

    // 3. Max nodes chosen where no two share an edge (Returns 1 for chosen nodes using 1-based indexing)
    vector<int> solve_max_independent_set() {
        vector<int> cover = solve_minimum_vertex_cover(); if (cover.empty()) return {};
        vector<int> mis(n + 1, 0);
        for (int i = 1; i <= n; i++) if (!cover[i]) mis[i] = 1;
        return mis;
    }

    // 4. Min disjoint paths to cover a DAG 
    int solve_disjoint_path_cover() {
        left_sz = n; right_sz = n; adj.assign(n + 1, vector<int>()); pair_u.assign(n + 1, -1); pair_v.assign(n + 1, -1); dist.resize(n + 1);
        for (int u = 1; u <= n; u++) {
            for (int v : orig_adj[u]) {
                // Internal transformations require 0-based mapping parameters for Hopcroft-Karp indices
                adj[u - 1].push_back(v - 1);
            }
        }
        int matching = 0;
        while (bfs()) for (int u = 0; u < left_sz; u++) if (pair_u[u] == -1 && dfs(u)) matching++;
        return n - matching;
    }

    // 5. Min overlapping paths to cover a DAG
    int solve_overlapping_path_cover() {
        vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
        for (int u = 1; u <= n; u++) for (int v : orig_adj[u]) reach[u][v] = true;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++) reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
        
        adj.assign(n + 1, vector<int>()); left_sz = n; right_sz = n; pair_u.assign(n + 1, -1); pair_v.assign(n + 1, -1); dist.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && reach[i][j]) adj[i - 1].push_back(j - 1);
            }
        }
        int matching = 0;
        while (bfs()) for (int u = 0; u < left_sz; u++) if (pair_u[u] == -1 && dfs(u)) matching++;
        return n - matching;
    }
};

// =========================================================================
// 2. WEIGHTED PERFECT MATCHING ENGINE (Hungarian) -> Time: O(V^3)
//    1-BASED INDEXING SUPPORTED: Rows and Cols span [1, n]
// =========================================================================
struct HungarianBlackBox {
    int n;
    vector<vector<long long>> cost, orig_cost;
    vector<long long> u, v;
    vector<int> p, way;

    HungarianBlackBox(int n) : n(n), cost(n + 1, vector<long long>(n + 1, LL_INF)), orig_cost(n + 1, vector<long long>(n + 1, LL_INF)),
        u(n + 1, 0), v(n + 1, 0), p(n + 1, 0), way(n + 1, 0) {}

    // Add weights between Left item (1 to n) and Right item (1 to n) directly
    void add_weight(int left_row, int right_col, long long w) { orig_cost[left_row][right_col] = w; }

    long long run_hungarian() {
        u.assign(n + 1, 0); v.assign(n + 1, 0); p.assign(n + 1, 0); way.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            p[0] = i; int j0 = 0; vector<long long> minv(n + 1, LL_INF); vector<bool> used(n + 1, false);
            do {
                used[j0] = true; int i0 = p[j0], j1 = 0; long long delta = LL_INF;
                for (int j = 1; j <= n; j++) {
                    if (!used[j]) {
                        long long cur = cost[i0][j] - u[i0] - v[j];
                        if (cur < minv[j]) { minv[j] = cur; way[j] = j0; }
                        if (minv[j] < delta) { delta = minv[j]; j1 = j; }
                    }
                }
                for (int j = 0; j <= n; j++) {
                    if (used[j]) { u[p[j]] += delta; v[j] -= delta; } else minv[j] -= delta;
                }
                j0 = j1;
            } while (p[j0] != 0);
            do { int j1 = way[j0]; p[j0] = p[j1]; j0 = j1; } while (j0 > 0);
        }
        return -v[0];
    }

    // 1. Min cost to pair everyone perfectly
    long long solve_min_weight_assignment() {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cost[i][j] = orig_cost[i][j];
        return run_hungarian();
    }

    // 2. Max profit to pair everyone perfectly
    long long solve_max_weight_assignment() {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cost[i][j] = (orig_cost[i][j] == LL_INF ? LL_INF : -orig_cost[i][j]);
        return -run_hungarian();
    }

    // 3. Min total weight to cover a general matrix graph using vertex-disjoint loops
    // Matrix parameter must be a 1-indexed vector mapping (size n+1 by n+1)
    long long solve_general_min_cycle_cover(const vector<vector<long long>>& general_matrix) {
        for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cost[i][j] = general_matrix[i][j];
        return run_hungarian();
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    return 0;
}
