class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        vector<int> best(n, INF);

        int left = 0;
        int sum = 0;
        int answer = INF;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink the window until sum <= target.
            while (sum > target) {
                sum -= arr[left];
                left++;
            }

            // Carry forward the shortest valid subarray seen so far.
            if (right > 0) {
                best[right] = best[right - 1];
            }

            if (sum == target) {
                int currentLength = right - left + 1;

                // Combine with a valid subarray entirely before this one.
                if (left > 0 && best[left - 1] != INF) {
                    answer = min(
                        answer,
                        best[left - 1] + currentLength
                    );
                }

                // Include the current subarray in the prefix minimum.
                best[right] = min(best[right], currentLength);
            }
        }

        return answer == INF ? -1 : answer;
    }
};