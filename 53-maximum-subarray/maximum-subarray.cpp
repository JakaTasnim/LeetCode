class Solution {
public:
    int maxSubArray(vector<int>& nums) {
       int n = nums.size();
       long long sum = 0 ;
       long long maxi = LONG_MIN;
       int start = 0 ;
       int ansStart = -1;
       int ansEnd = -1;
       for(int i = 0 ; i < n ; i++){
            sum += nums[i];
            if(sum == 0){
                start = i;
            }
            if(sum > maxi ){
                maxi = sum;
                ansStart = start;
                ansEnd = i;
            }
            if(sum < 0 ){
                sum = 0;
            }
        } 
    return maxi;
    }
};