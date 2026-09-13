class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1,
                       vector<vector<int>>& img2) {
        int n = img1.size();

        vector<pair<int, int>> ones1, ones2;

        // Collect positions containing 1.
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (img1[r][c] == 1) {
                    ones1.push_back({r, c});
                }

                if (img2[r][c] == 1) {
                    ones2.push_back({r, c});
                }
            }
        }

        // Shifts range from -(n - 1) to +(n - 1).
        // Adding offset makes every array index non-negative.
        int offset = n - 1;
        vector<vector<int>> shiftCount(
            2 * n - 1, vector<int>(2 * n - 1, 0)
        );

        int answer = 0;

        for (const auto& [r1, c1] : ones1) {
            for (const auto& [r2, c2] : ones2) {
                int rowShift = r2 - r1 + offset;
                int colShift = c2 - c1 + offset;

                ++shiftCount[rowShift][colShift];

                answer = max(
                    answer,
                    shiftCount[rowShift][colShift]
                );
            }
        }

        return answer;
    }
};