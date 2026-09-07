class Solution {
public:
    int distinctSubseqII(string s) {

        const long long MOD = 1e9 + 7;

        int n = s.size();

        vector<long long> dp(n + 1);

        dp[0] = 1;

        vector<int> last(26, -1);

        for (int i = 1; i <= n; i++) {

            int c = s[i - 1] - 'a';

            dp[i] = (2 * dp[i - 1]) % MOD;

            if (last[c] != -1) {

                dp[i] = (
                    dp[i] - dp[last[c]] + MOD
                ) % MOD;
            }

            last[c] = i - 1;
        }

        return (dp[n] - 1 + MOD) % MOD;
    }
};