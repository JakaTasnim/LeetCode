class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));

        priority_queue<
            pair<int, pair<int,int>>,
            vector<pair<int, pair<int,int>>>,
            greater<pair<int, pair<int,int>>>
        > pq;

        dist[0][0] = grid[0][0];
        pq.push({dist[0][0], {0, 0}});

        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};

        while(!pq.empty()) {
            auto cur = pq.top();
            pq.pop();

            int cost = cur.first;
            int x = cur.second.first;
            int y = cur.second.second;

            if(cost > dist[x][y]) continue;

            for(int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];

                if(nx < 0 || ny < 0 || nx >= m || ny >= n)
                    continue;

                int newCost = cost + grid[nx][ny];

                if(newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    pq.push({newCost, {nx, ny}});
                }
            }
        }

        return dist[m-1][n-1] < health;
    }
};