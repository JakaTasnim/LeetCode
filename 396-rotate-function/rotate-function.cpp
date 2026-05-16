class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
         int n = nums.size();

        long long sum = 0;
        long long f = 0;
        for(int i = 0; i < n; i++) {
            sum += nums[i];
            f += (long long)i * nums[i];
        }

        long long ans = f;
        for(int k = 1; k < n; k++) {

            f = f + sum - (long long)n * nums[n - k];

            ans = max(ans, f);
        }

        return ans;
    }
};