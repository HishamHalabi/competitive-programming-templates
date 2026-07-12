#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct McmfComplete {
    struct Edge {
        int from;
        int to;
        int rev;
        int cap;
        int flow;
        ll cost;
        int original_id; // Track index from input sequence
    };

    int n;
    bool has_neg;
    vector<vector<Edge>> adj;
    vector<ll> h; // Node potentials for Dijkstra adjustment

    /**
     * @param n Number of vertices.
     * @param has_negative_edges Set to true if the initial graph contains negative edge costs.
     */
    McmfComplete(int n, bool has_negative_edges = false) 
        : n(n), has_neg(has_negative_edges), adj(n + 1), h(n + 1, 0) {}

    /**
     * Adds a directed edge into the network.
     */
    void add_edge(int from, int to, int cap, ll cost, int id = -1) {
        adj[from].push_back({from, to, (int)adj[to].size(), cap, 0, cost, id});
        adj[to].push_back({to, from, (int)adj[from].size() - 1, 0, 0, -cost, -1});
    }

private:
    // Internal SPFA helper to establish initial potentials for negative edges
    bool run_initial_spfa(int src) {
        fill(h.begin(), h.end(), INF);
        vector<bool> in_queue(n + 1, false);
        vector<int> cnt(n + 1, 0);
        queue<int> q;

        h[src] = 0;
        q.push(src);
        in_queue[src] = true;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            in_queue[u] = false;

            for (const auto& e : adj[u]) {
                if (e.cap - e.flow > 0 && h[u] + e.cost < h[e.to]) {
                    h[e.to] = h[u] + e.cost;
                    if (!in_queue[e.to]) {
                        q.push(e.to);
                        in_queue[e.to] = true;
                        if (++cnt[e.to] > n) return false; // Found a negative cycle
                    }
                }
            }
        }
        return true;
    }

    // Core execution method
    pair<int, ll> compute_flow(int src, int sink, int target_flow, bool strict_target) {
        if (has_neg) {
            if (!run_initial_spfa(src)) return {-1, -1}; // Negative cycle safety exit
        }

        ll total_cost = 0;
        int flow_sent = 0;

        while (flow_sent < target_flow) {
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
            vector<ll> dist(n + 1, INF);
            vector<int> parent_node(n + 1, -1);
            vector<int> parent_edge(n + 1, -1);

            dist[src] = 0;
            pq.push({0, src});

            while (!pq.empty()) {
                auto [d, u] = pq.top(); pq.pop();
                if (d > dist[u]) continue;

                for (int i = 0; i < adj[u].size(); ++i) {
                    const Edge& e = adj[u][i];
                    ll reduced_cost = e.cost + h[u] - h[e.to];
                    
                    if (e.cap - e.flow > 0 && dist[u] + reduced_cost < dist[e.to]) {
                        dist[e.to] = dist[u] + reduced_cost;
                        parent_node[e.to] = u;
                        parent_edge[e.to] = i;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }

            if (dist[sink] == INF) {
                if (strict_target) return {-1, -1}; // Failed to reach target flow exactly
                break;
            }

            for (int i = 1; i <= n; ++i) {
                if (dist[i] != INF) h[i] += dist[i];
            }

            int push = target_flow - flow_sent;
            int curr = sink;
            while (curr != src) {
                int p = parent_node[curr];
                int idx = parent_edge[curr];
                push = min(push, adj[p][idx].cap - adj[p][idx].flow);
                curr = p;
            }

            curr = sink;
            while (curr != src) {
                int p = parent_node[curr];
                int idx = parent_edge[curr];
                adj[p][idx].flow += push;
                adj[curr][adj[p][idx].rev].flow -= push;
                curr = p;
            }

            flow_sent += push;
            total_cost += (ll)push * h[sink]; 
        }

        return {flow_sent, total_cost};
    }

    // Helper DFS to pull routing chains based on positive flow tracking
    bool find_flow_path(int u, int sink, vector<int>& current_path, vector<Edge*>& edge_pointers) {
        if (u == sink) return true;
        for (auto& e : adj[u]) {
            if (e.cap > 0 && e.flow > 0) {
                current_path.push_back(e.to);
                edge_pointers.push_back(&e);
                if (find_flow_path(e.to, sink, current_path, edge_pointers)) return true;
                current_path.pop_back();
                edge_pointers.pop_back();
            }
        }
        return false;
    }

public:
    /**
     * API 1: Finds the min cost to send EXACTLY target_flow.
     */
    pair<int, ll> get_exact_flow_min_cost(int src, int sink, int target_flow) {
        return compute_flow(src, sink, target_flow, true);
    }

    /**
     * API 2: Finds the min cost to send the MAXIMUM POSSIBLE FLOW.
     */
    pair<int, ll> get_max_flow_min_cost(int src, int sink, int max_flow_limit = 2e9) {
        return compute_flow(src, sink, max_flow_limit, false);
    }

    /**
     * FEATURE 1: Extracts edges forming the Min-Cost Min-Cut boundary.
     * MUST be called strictly AFTER a flow method has completed execution.
               A Quick Cheat Sheet to Remember the Difference:
              Dinic Cut: The minimum capacity required to stop any flow.
              MCMF Cut: The minimum capacity required to stop the cheapest flow.
     */
    vector<Edge> get_min_cut_edges(int src) {
        vector<bool> visited(n + 1, false);
        queue<int> q;
        
        q.push(src);
        visited[src] = true;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const auto& e : adj[u]) {
                if (e.cap - e.flow > 0 && !visited[e.to]) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }

        vector<Edge> cut_edges;
        for (int u = 1; u <= n; ++u) {
            if (visited[u]) {
                for (const auto& e : adj[u]) {
                    if (!visited[e.to] && e.cap > 0) {
                        cut_edges.push_back(e);
                    }
                }
            }
        }
        return cut_edges;
    }

    /**
     * FEATURE 2: Decomposes optimal flow metrics back into discrete routing paths.
     * MUST be called strictly AFTER flow execution. Modifies edge flows.
     */
    vector<vector<int>> extract_flow_paths(int src, int sink) {
        vector<vector<int>> all_paths;
        while (true) {
            vector<int> current_path = {src};
            vector<Edge*> edge_pointers;
            
            if (!find_flow_path(src, sink, current_path, edge_pointers)) break;
            
            int path_flow = 2e9;
            for (auto* e_ptr : edge_pointers) {
                path_flow = min(path_flow, e_ptr->flow);
            }
            for (auto* e_ptr : edge_pointers) {
                e_ptr->flow -= path_flow;
            }
            for (int i = 0; i < path_flow; ++i) {
                all_paths.push_back(current_path);
            }
        }
        return all_paths;
    }
};
