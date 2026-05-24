class Solution {
public:

    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();

        dp.resize(n, -1);

        int result = 1;

        for (int i = 0; i < n; i++) {

            result = max(result, dfs(arr, d, i));
        }

        return result;
    }
    vector<int> dp;

    int dfs(vector<int>& arr, int d, int i) {

        // Already calculated
        if (dp[i] != -1)
            return dp[i];

        int n = arr.size();

        int ans = 1;

        // Right side
        for (int j = i + 1; j <= min(n - 1, i + d); j++) {

            if (arr[j] >= arr[i])
                break;

            ans = max(ans, 1 + dfs(arr, d, j));
        }

        // Left side
        for (int j = i - 1; j >= max(0, i - d); j--) {

            if (arr[j] >= arr[i])
                break;

            ans = max(ans, 1 + dfs(arr, d, j));
        }

        return dp[i] = ans;
    }
};