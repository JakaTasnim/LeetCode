class Solution {
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }

            ++left;
            --right;
        }

        return true;
    }

public:
    int maxPalindromes(const string& s, int k) {
        int n = s.size();
        int answer = 0;
        int nextStart = 0;

        for (int end = k - 1; end < n; ++end) {
            int start = end - k + 1;

            if ((start >= nextStart &&
                 isPalindrome(s, start, end)) ||
                (start - 1 >= nextStart &&
                 isPalindrome(s, start - 1, end))) {

                ++answer;

                nextStart = end + 1;
            }
        }

        return answer;
    }
};