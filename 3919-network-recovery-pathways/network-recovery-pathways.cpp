class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        using ll = long long;
        int n = online.size();

        vector<vector<pair<int,int>>> graph(n);
        vector<int> indegree(n, 0);

        int mxEdge = 0;

        for (auto &e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            indegree[e[1]]++;
            mxEdge = max(mxEdge, e[2]);
        }

        // Topological Order
        vector<int> topo;
        queue<int> q;
        vector<int> indeg = indegree;

        for (int i = 0; i < n; i++)
            if (indeg[i] == 0)
                q.push(i);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto &[v, w] : graph[u]) {
                if (--indeg[v] == 0)
                    q.push(v);
            }
        }

        auto check = [&](int limit) {

            const ll INF = 4e18;

            vector<ll> dist(n, INF);
            dist[0] = 0;

            for (int u : topo) {

                if (dist[u] == INF)
                    continue;

                if (u != 0 && u != n - 1 && !online[u])
                    continue;

                for (auto &[v, w] : graph[u]) {

                    if (w < limit)
                        continue;

                    if (v != n - 1 && !online[v])
                        continue;

                    dist[v] = min(dist[v], dist[u] + (ll)w);
                }
            }

            return dist[n - 1] <= k;
        };

        int lo = 0;
        int hi = mxEdge;
        int ans = -1;

        while (lo <= hi) {

            int mid = lo + (hi - lo) / 2;

            if (check(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans; 
    }
};