class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = n - 1; i >= 0; i--) {

            for (int M = 1; M <= n; M++) {

                if (i + 2 * M >= n) {
                    dp[i][M] = suffix[i];
                    continue;
                }

                int best = 0;

                for (int X = 1; X <= 2 * M; X++) {

                    int newM = max(M, X);

                    int current =
                        suffix[i] - dp[i + X][newM];

                    best = max(best, current);
                }

                dp[i][M] = best;
            }
        }
        return dp[0][1];
    }
};