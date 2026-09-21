class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            // Counts for subarrays ending at the current index.
            vector<long long> current(k, 0);

            int remainder = num % k;

            // 1. Start a new subarray containing only num.
            current[remainder]++;

            // 2. Extend every subarray ending at the previous index.
            for (int r = 0; r < k; r++) {
                int newRemainder = (r * remainder) % k;
                current[newRemainder] += dp[r];
            }

            // Add these subarrays to the overall answer.
            for (int r = 0; r < k; r++) {
                result[r] += current[r];
            }

            dp = current;
        }

        return result;
    }
};