class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {

        int n = s.size();

        string ans = "";

        for (int i = 0; i < n; i++) {

            int ones = 0;

            for (int j = i; j < n; j++) {

                if (s[j] == '1') {
                    ones++;
                }

                // Exactly k ones
                if (ones == k) {

                    string current = s.substr(i, j - i + 1);

                    // First valid substring
                    // OR shorter substring
                    // OR same length but lexicographically smaller
                    if (ans == "" ||
                        current.length() < ans.length() ||
                        (current.length() == ans.length() && current < ans)) {

                        ans = current;
                    }

                    break;
                }

                // Once ones > k, this starting point
                // cannot produce a beautiful substring anymore.
                if (ones > k) {
                    break;
                }
            }
        }

        return ans;
    }
};