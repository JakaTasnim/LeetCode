class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();
        
        vector<bool> reachable(n, false);
        reachable[0] = true;

        int reachableCount = 0;

        for (int i = 1; i < n; i++) {

            // Add new index entering the window
            if (i - minJump >= 0 && reachable[i - minJump]) {
                reachableCount++;
            }

            // Remove index leaving the window
            if (i - maxJump - 1 >= 0 && reachable[i - maxJump - 1]) {
                reachableCount--;
            }

            // Current index can be reached
            if (s[i] == '0' && reachableCount > 0) {
                reachable[i] = true;
            }
        }

        return reachable[n - 1]; 
    }
};