class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {

        const int MAXX = 2048;

        vector<int> two(MAXX, 0);
        vector<int> three(MAXX, 0);

        int n = nums.size();

        // XOR of every pair
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                two[nums[i] ^ nums[j]] = 1;
            }
        }

        // XOR with third element
        for (int x = 0; x < MAXX; x++) {
            if (!two[x]) continue;

            for (int v : nums) {
                three[x ^ v] = 1;
            }
        }

        int ans = 0;

        for (int x = 0; x < MAXX; x++)
            ans += three[x];

        return ans;
    }
};