class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        int maxCost = *max_element(costs.begin(), costs.end());

        vector<int> freq(maxCost + 1, 0);

        for (int cost : costs)
            freq[cost]++;

        int ans = 0;

        for (int cost = 1; cost <= maxCost; cost++) {

            while (freq[cost] > 0 && coins >= cost) {
                coins -= cost;
                ans++;
                freq[cost]--;
            }
        }

        return ans;  
    }
};