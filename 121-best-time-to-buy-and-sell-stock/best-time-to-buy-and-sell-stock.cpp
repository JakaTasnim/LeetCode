class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;

        for(int price : prices) {

            // Update minimum buying price
            minPrice = min(minPrice, price);

            // Calculate current profit
            int profit = price - minPrice;

            // Update maximum profit
            maxProfit = max(maxProfit, profit);
        }

        return maxProfit; 
    }
};