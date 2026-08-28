class Solution {
public:

    string makePalindrome(string left, char middle) {
        string right = left;
        reverse(right.begin(), right.end());

        if (middle == '#')
            return left + right;

        return left + string(1, middle) + right;
    }

    string lexPalindromicPermutation(string s, string target) {

        int n = s.size();
        int half = n / 2;

        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        int odd = 0;
        char middle = '#';

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                middle = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        vector<int> halfFreq(26);

        for (int i = 0; i < 26; i++) {
            halfFreq[i] = freq[i] / 2;
        }

        string targetLeft = target.substr(0, half);
        vector<vector<int>> rem(
            half + 1,
            vector<int>(26)
        );

        rem[0] = halfFreq;

        int matched = 0;

        for (int i = 0; i < half; i++) {

            rem[i + 1] = rem[i];

            int c = targetLeft[i] - 'a';

            if (rem[i + 1][c] == 0)
                break;

            rem[i + 1][c]--;
            matched++;
        }


        if (matched == half) {

            string candidate =
                makePalindrome(targetLeft, middle);

            if (candidate > target)
                return candidate;
        }

        int startPos;

        if (matched < half)
            startPos = matched;
        else
            startPos = half - 1;

        for (int pos = startPos; pos >= 0; pos--) {

            vector<int> remaining = rem[pos];

            int targetChar = targetLeft[pos] - 'a';

            for (int c = targetChar + 1; c < 26; c++) {

                if (remaining[c] == 0)
                    continue;

                remaining[c]--;

                string left = targetLeft.substr(0, pos);

                left += char('a' + c);

                for (int x = 0; x < 26; x++) {

                    while (remaining[x] > 0) {

                        left += char('a' + x);
                        remaining[x]--;
                    }
                }

                string candidate =
                    makePalindrome(left, middle);

                if (candidate > target)
                    return candidate;
            }
        }

        return "";
    }
};