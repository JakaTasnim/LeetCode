class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();

        // If already at last index
        if(n == 1) {
            return 0;
        }

        // Store indices for each value
        unordered_map<int, vector<int>> mp;

        for(int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }

        queue<int> q;
        vector<bool> visited(n, false);

        q.push(0);
        visited[0] = true;

        int steps = 0;

        while(!q.empty()) {

            int size = q.size();

            while(size--) {

                int curr = q.front();
                q.pop();

                // Reached last index
                if(curr == n - 1) {
                    return steps;
                }

                vector<int> neighbors;

                // Same value indices
                for(int idx : mp[arr[curr]]) {
                    neighbors.push_back(idx);
                }

                // Adjacent indices
                neighbors.push_back(curr + 1);
                neighbors.push_back(curr - 1);

                for(int next : neighbors) {

                    if(next >= 0 && next < n && !visited[next]) {

                        visited[next] = true;
                        q.push(next);
                    }
                }

                // Important optimization
                mp[arr[curr]].clear();
            }

            steps++;
        }

        return -1;
    }
};