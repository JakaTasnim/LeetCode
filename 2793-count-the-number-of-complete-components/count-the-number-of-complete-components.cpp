class Solution {
public:
    vector<vector<int>> adj;
    vector<int> vis;

    void dfs(int node, int &nodes, int &degreeSum) {
        vis[node] = 1;
        nodes++;
        degreeSum += adj[node].size();

        for (int nei : adj[node]) {
            if (!vis[nei]) {
                dfs(nei, nodes, degreeSum);
            }
        }
    }
    
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        adj.resize(n);
        vis.assign(n, 0);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {

            if (!vis[i]) {

                int nodes = 0;
                int degreeSum = 0;

                dfs(i, nodes, degreeSum);

                int actualEdges = degreeSum / 2;
                int requiredEdges = nodes * (nodes - 1) / 2;

                if (actualEdges == requiredEdges)
                    ans++;
            }
        }

        return ans;  
    }
};