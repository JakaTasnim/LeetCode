class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = arr.size();

        vector<bool> visited(n, false);

        queue<int> q;
        q.push(start);

        visited[start] = true;

        while(!q.empty()) {

            int index = q.front();
            q.pop();

            // Found value 0
            if(arr[index] == 0) {
                return true;
            }

            int forward = index + arr[index];
            int backward = index - arr[index];

            // Forward jump
            if(forward < n && !visited[forward]) {
                visited[forward] = true;
                q.push(forward);
            }

            // Backward jump
            if(backward >= 0 && !visited[backward]) {
                visited[backward] = true;
                q.push(backward);
            }
        }

        return false;
        
    }
};