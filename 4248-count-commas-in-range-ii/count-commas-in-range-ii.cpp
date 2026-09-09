class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        for (long long threshold = 1000;
             threshold <= n;
             threshold *= 1000) {

            ans += n - threshold + 1;

            // Prevent long long overflow
            if (threshold > n / 1000)
                break;
        }

        return ans;
    }
};