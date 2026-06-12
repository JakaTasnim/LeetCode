class Solution {
public:
    static const int MOD = 1e9 + 7;
    static const int LOG = 20;

    vector<vector<int>> adj;
    vector<vector<int>> up;
    vector<int> depth;
    vector<long long> pow2;

    void dfs(int u, int p) {
        up[u][0] = p;

        for (int i = 1; i < LOG; i++) {
            if (up[u][i - 1] == -1)
                up[u][i] = -1;
            else
                up[u][i] = up[up[u][i - 1]][i - 1];
        }

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    int lca(int u, int v) {

        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int i = LOG - 1; i >= 0; i--) {
            if ((diff >> i) & 1)
                u = up[u][i];
        }

        if (u == v)
            return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

    vector<int> assignEdgeWeights(vector<vector<int>>& edges,vector<vector<int>>& queries) {

        int n = edges.size() + 1;

        adj.assign(n + 1, {});
        up.assign(n + 1, vector<int>(LOG, -1));
        depth.assign(n + 1, 0);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(1, -1);

        pow2.assign(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            pow2[i] = (pow2[i - 1] * 2LL) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {

            int u = q[0];
            int v = q[1];

            int w = lca(u, v);

            int len = depth[u] + depth[v] - 2 * depth[w];

            if (len == 0)
                ans.push_back(0);
            else
                ans.push_back(pow2[len - 1]);
        }

        return ans;
    }
};