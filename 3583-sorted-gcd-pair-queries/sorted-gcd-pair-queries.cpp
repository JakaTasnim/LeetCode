class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int mx = *max_element(nums.begin(), nums.end());

        vector<long long> freq(mx + 1, 0);

        for (int x : nums)
            freq[x]++;

        // cnt[g] = numbers divisible by g
        vector<long long> cnt(mx + 1, 0);

        for (int g = 1; g <= mx; g++) {
            for (int j = g; j <= mx; j += g)
                cnt[g] += freq[j];
        }

        // exactPairs[g] = pairs having gcd exactly g
        vector<long long> exactPairs(mx + 1, 0);

        for (int g = mx; g >= 1; g--) {

            long long pairs = cnt[g] * (cnt[g] - 1) / 2;

            for (int j = 2 * g; j <= mx; j += g)
                pairs -= exactPairs[j];

            exactPairs[g] = pairs;
        }

        // prefix counts
        vector<long long> pref(mx + 1, 0);

        for (int g = 1; g <= mx; g++)
            pref[g] = pref[g - 1] + exactPairs[g];

        vector<int> ans;

        for (long long q : queries) {

            int g = lower_bound(pref.begin() + 1, pref.end(), q + 1) - pref.begin();

            ans.push_back(g);
        }

        return ans; 
    }
};