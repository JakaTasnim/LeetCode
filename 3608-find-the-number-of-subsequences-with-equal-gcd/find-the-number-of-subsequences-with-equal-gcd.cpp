class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAXV = 201; 
        

        vector<vector<long long>> dp(MAXV, vector<long long>(MAXV, 0));
        dp[0][0] = 1; 
        
        for (int x : nums) {
            vector<vector<long long>> newDp = dp;
            
            for (int g1 = 0; g1 < MAXV; g1++) {
                for (int g2 = 0; g2 < MAXV; g2++) {
                    long long ways = dp[g1][g2];
                    if (ways == 0) continue;
                    

                    int ng1 = (g1 == 0) ? x : __gcd(g1, x);
                    newDp[ng1][g2] = (newDp[ng1][g2] + ways) % MOD;
                    

                    int ng2 = (g2 == 0) ? x : __gcd(g2, x);
                    newDp[g1][ng2] = (newDp[g1][ng2] + ways) % MOD;
                }
            }
            
            dp = move(newDp);
        }
        
        long long answer = 0;
        for (int g = 1; g < MAXV; g++) {
            answer = (answer + dp[g][g]) % MOD;
        }
        
        return (int)answer;
    }
};