#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;
const ll INF = 1e18;

struct DinicComplete {
    struct Edge {
        int from;
        int to;
        int rev;
        ll cap;
        ll flow;
        int original_id; // For tracking edge indexing from input
    };

    int n;
    vector<vector<Edge>> adj;
    vector<int> level, ptr;

    DinicComplete(int n) : n(n), adj(n + 1), level(n + 1), ptr(n + 1) {}

    /**
     * Adds a directed edge into the network.
     * @param id Optional identifier for tracking original graph input sequences.
     */
    void add_edge(int from, int to, ll cap, int id = -1) {
        adj[from].push_back({from, to, (int)adj[to].size(), cap, 0, id});
        adj[to].push_back({to, from, (int)adj[from].size() - 1, 0, 0, -1});
    }

private:
    bool bfs(int src, int sink) {
        fill(level.begin(), level.end(), -1);
        level[src] = 0;
        queue<int> q;
        q.push(src);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const auto& e : adj[u]) {
                if (e.cap - e.flow > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[sink] != -1;
    }

    ll dfs(int u, int sink, ll pushed) {
        if (pushed == 0 || u == sink) return pushed;
        for (int& cid = ptr[u]; cid < adj[u].size(); ++cid) {
            auto& e = adj[u][cid];
            if (level[u] + 1 != level[e.to] || e.cap - e.flow == 0) continue;
            ll tr_pushed = dfs(e.to, sink, min(pushed, e.cap - e.flow));
            if (tr_pushed == 0) continue;
            e.flow += tr_pushed;
            adj[e.to][e.rev].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    // Helper DFS to extract paths by looking for active flow
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
     * Computes the maximum possible flow from source to sink.
     */
    ll get_max_flow(int src, int sink) {
        ll flow = 0;
        while (bfs(src, sink)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (ll pushed = dfs(src, sink, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    /**
     * FEATURE 1: Extracts the edges that form the minimum cut bottleneck.
     * MUST be called strictly AFTER calling get_max_flow().
     * @return A list of forward edges spanning from the Source component to the Sink component.
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
     * FEATURE 2: Decomposes structural flow fields back into individual simple paths.
     * MUST be called strictly AFTER calling get_max_flow() and BEFORE changing edge states.
     * @return A vector of paths, where each path is a sequence of node IDs.
A cut is a choice of pipes that you decide to slice open with a saw. Your goal when making a cut is absolute disruption: You want to completely cut off the water supply so that not a single drop of water can reach your house.


A Minimum Cut (Min-Cut) is the cheapest way to do this. You want to find a set of pipes to cut such that:

The water is completely stopped.

The total capacity of the pipes you cut is as small (minimum) as possible.
     */
    vector<vector<int>> extract_flow_paths(int src, int sink) {
        vector<vector<int>> all_paths;
        while (true) {
            vector<int> current_path = {src};
            vector<Edge*> edge_pointers;
            
            if (!find_flow_path(src, sink, current_path, edge_pointers)) break;
            
            ll path_flow = INF;
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
