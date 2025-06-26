#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int M = 26;

int trie[N][M], go[N][M], suffix[N], exit_link[N];
bool leaf[N];
int idx[15]; // end nodes of patterns (for up to 15 patterns)
int ptr = 1;

void insert(const string& s, int id) {
    int node = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (!trie[node][c]) trie[node][c] = ptr++;
        node = trie[node][c];
    }
    leaf[node] = true;
    idx[id] = node;
}

void dfs(int node, vector<bool>& vis) {
    if (node == 0 || vis[node]) return;
    vis[node] = true;
    dfs(suffix[node], vis);
    exit_link[node] = leaf[suffix[node]] ? suffix[node] : exit_link[suffix[node]];
}

void build() {
    queue<int> q;
    for (int i = 0; i < M; ++i) {
        go[0][i] = trie[0][i];
        if (trie[0][i]) q.push(trie[0][i]);
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int c = 0; c < M; ++c) {
            if (trie[u][c]) {
                int v = trie[u][c];
                int f = suffix[u];
                while (f && !trie[f][c]) f = suffix[f];
                suffix[v] = trie[f][c];
                q.push(v);
            }
            go[u][c] = trie[u][c] ? trie[u][c] : go[suffix[u]][c];
        }
    }

    vector<bool> vis(ptr, false);
    for (int i = 0; i < ptr; ++i)
        dfs(i, vis);
}

// --- Function 1: Lex smallest string of length L NOT matching any pattern
string lex_smallest_excluding(int L) {
    struct State {
        int node, len;
        string s;
        bool operator<(const State& o) const {
            return s > o.s; // min lex
        }
    };
    priority_queue<State> pq;
    pq.push({0, 0, ""});
    while (!pq.empty()) {
        auto [node, len, s] = pq.top(); pq.pop();
        if (len == L) return s;
        for (int c = 0; c < M; ++c) {
            int next = go[node][c];
            if (leaf[next]) continue;
            pq.push({next, len + 1, s + char('a' + c)});
        }
    }
    return "-1";
}

// --- Function 2: Shortest string containing all patterns
string shortest_covering_all(int k) {
    const int MAXK = 12;
    vector<vector<int>> dist(ptr, vector<int>(1 << k, -1));
    queue<tuple<int, int>> q;

    dist[0][0] = 0;
    q.push({0, 0});
    while (!q.empty()) {
        auto [node, mask] = q.front(); q.pop();
        for (int c = 0; c < M; ++c) {
            int next = go[node][c];
            int new_mask = mask;
            for (int t = next; t; t = exit_link[t]) {
                for (int i = 0; i < k; ++i)
                    if (idx[i] == t)
                        new_mask |= (1 << i);
            }
            if (dist[next][new_mask] == -1) {
                dist[next][new_mask] = dist[node][mask] + 1;
                q.push({next, new_mask});
            }
        }
    }

    int min_len = INT_MAX;
    for (int i = 0; i < ptr; ++i)
        if (dist[i][(1 << k) - 1] != -1)
            min_len = min(min_len, dist[i][(1 << k) - 1]);

    return to_string(min_len); // or reconstruct path
}

// --- Function 3: Lex smallest string of length L containing all k patterns
string lex_smallest_with_all(int L, int k) {
    struct State {
        int node, len, mask;
        string s;
        bool operator<(const State& o) const {
            return s > o.s;
        }
    };

    priority_queue<State> pq;
    pq.push({0, 0, 0, ""});
    unordered_map<int, unordered_map<int, bool>> seen;

    while (!pq.empty()) {
        auto [node, len, mask, s] = pq.top(); pq.pop();
        if (len == L && mask == (1 << k) - 1)
            return s;
        if (len >= L) continue;
        for (int c = 0; c < M; ++c) {
            int next = go[node][c];
            int new_mask = mask;
            for (int t = next; t; t = exit_link[t]) {
                for (int i = 0; i < k; ++i)
                    if (idx[i] == t)
                        new_mask |= (1 << i);
            }
            if (!seen[next][new_mask]) {
                seen[next][new_mask] = true;
                pq.push({next, len + 1, new_mask, s + char('a' + c)});
            }
        }
    }

    return "-1";
}
/*
📌 Summary Table
Component / Function	Time Complexity	Space Complexity
Aho-Corasick Build	O(total pattern length × 26)	O(N × 26)
Lex Smallest Excluding Patterns (Len = L)	O(L × N × log Q)	O(L × N)
Shortest String Covering All Patterns	O(N × 2^k × 26)	O(N × 2^k)
Lex Smallest String of Length L Containing All	O(L × N × 2^k × log Q)	O(N × 2^k)
*/
int main() {
    int k = 3, L = 10;
    vector<string> patterns = {"ab", "bc", "cd"};
    for (int i = 0; i < k; ++i)
        insert(patterns[i], i);
    build();

    cout << "1. Lex smallest NOT matching: " << lex_smallest_excluding(L) << '\n';
    cout << "2. Shortest containing ALL: " << shortest_covering_all(k) << '\n';
    cout << "3. Lex smallest length " << L << " containing all: " << lex_smallest_with_all(L, k) << '\n';
}

