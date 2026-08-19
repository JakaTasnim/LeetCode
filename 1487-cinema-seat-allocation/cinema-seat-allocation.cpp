class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Only seats 2 to 9 matter
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            if (s >= 2 && s <= 9) {
                mp[row] |= (1 << s);
            }
        }

        // Rows having no relevant reservation
        long long ans = 2LL * (n - mp.size());

        // Process rows that have reservations
        for (auto &[row, mask] : mp) {
            bool left = true;   // 2,3,4,5
            bool middle = true; // 4,5,6,7
            bool right = true;  // 6,7,8,9

            // Check seats 2,3,4,5
            for (int s = 2; s <= 5; s++) {
                if (mask & (1 << s)) {
                    left = false;
                    break;
                }
            }

            // Check seats 4,5,6,7
            for (int s = 4; s <= 7; s++) {
                if (mask & (1 << s)) {
                    middle = false;
                    break;
                }
            }

            // Check seats 6,7,8,9
            for (int s = 6; s <= 9; s++) {
                if (mask & (1 << s)) {
                    right = false;
                    break;
                }
            }

            if (left && right) {
                // Both groups can sit: 2-5 and 6-9
                ans += 2;
            }
            else if (left || middle || right) {
                // At least one block is possible
                ans += 1;
            }
        }

        return (int)ans;
    }
};