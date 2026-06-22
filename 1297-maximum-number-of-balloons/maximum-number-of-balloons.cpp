class Solution {
public:
    int maxNumberOfBalloons(string text) {
        vector<int> freq(26, 0);

        // Count frequency of every character
        for (char ch : text) {
            freq[ch - 'a']++;
        }

        // Return minimum possible balloons
        return min({
            freq['b' - 'a'],
            freq['a' - 'a'],
            freq['l' - 'a'] / 2,
            freq['o' - 'a'] / 2,
            freq['n' - 'a']
        });  
    }
};