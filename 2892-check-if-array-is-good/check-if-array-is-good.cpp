class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = *max_element(nums.begin(), nums.end());
        if (nums.size() != n + 1) return false;
        vector<int> freq(n + 1, 0);

        for (int num : nums) {
            if (num > n) return false;
            freq[num]++;
        }
        for (int i = 1; i < n; i++) {
            if (freq[i] != 1) return false;
        }
        if (freq[n] != 2) return false;

        return true;
    }
};