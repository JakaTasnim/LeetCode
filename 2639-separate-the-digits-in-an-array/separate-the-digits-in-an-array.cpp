class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> result;
        
        for(int num : nums) {
            string s = to_string(num);  // convert number to string
            
            for(char ch : s) {
                result.push_back(ch - '0'); // convert char to int
            }
        }
        
        return result;  
    }
};