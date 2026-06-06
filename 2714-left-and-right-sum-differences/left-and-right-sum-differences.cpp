class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int totalSum = 0;

        for (int x : nums)
            totalSum += x;

        int leftSum = 0;
        vector<int> answer;

        for (int i = 0; i < nums.size(); i++) {

            int rightSum = totalSum - leftSum - nums[i];

            answer.push_back(abs(leftSum - rightSum));

            leftSum += nums[i];
        }

        return answer; 
    }
};