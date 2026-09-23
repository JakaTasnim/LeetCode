class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();

        long long totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        long long target = totalSum - x;

        // Even removing all elements cannot reduce x to 0.
        if (target < 0) return -1;

        // All elements are positive, so we must remove everything.
        if (target == 0) return n;

        int left = 0;
        int maxLength = -1;
        long long windowSum = 0;

        for (int right = 0; right < n; right++) {
            windowSum += nums[right];

            // Shrink until the window sum is at most target.
            while (windowSum > target) {
                windowSum -= nums[left];
                left++;
            }

            if (windowSum == target) {
                maxLength = max(maxLength, right - left + 1);
            }
        }

        return maxLength == -1 ? -1 : n - maxLength;
    }
};