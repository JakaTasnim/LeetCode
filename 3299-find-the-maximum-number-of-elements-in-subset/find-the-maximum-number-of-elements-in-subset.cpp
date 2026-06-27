class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;

        for (int x : nums)
            cnt[x]++;

        int ans = 1;

        // Handle value 1 separately
        if (cnt.count(1)) {
            int c = cnt[1];
            if (c % 2 == 0)
                ans = max(ans, c - 1);
            else
                ans = max(ans, c);
        }

        for (auto &[start, f] : cnt) {

            if (start == 1) continue;

            long long cur = start;
            int len = 0;

            while (cnt.count(cur)) {

                if (cnt[cur] >= 2) {
                    len += 2;
                } else {
                    len += 1;
                    break;
                }

                // prevent overflow
                if (cur > 1000000000LL) break;

                long long nxt = cur * cur;

                if (nxt > (long long)4e18 / max(1LL, cur))
                    break;

                cur = nxt;
            }

            if (len % 2 == 0)
                len--;

            ans = max(ans, len);
        }

        return ans;
    }
};