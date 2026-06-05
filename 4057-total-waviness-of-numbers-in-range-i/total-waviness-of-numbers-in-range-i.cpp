class Solution {
public:
    int waviness(int num) {

        string s = to_string(num);
        int n = s.size();

        if (n < 3) return 0;

        int cnt = 0;

        for (int i = 1; i < n - 1; i++) {

            int left = s[i - 1] - '0';
            int cur  = s[i] - '0';
            int right = s[i + 1] - '0';

            // Peak
            if (cur > left && cur > right)
                cnt++;

            // Valley
            else if (cur < left && cur < right)
                cnt++;
        }

        return cnt;
    }

    long long totalWaviness(int num1, int num2) {

        long long ans = 0;

        for (int x = num1; x <= num2; x++) {
            ans += waviness(x);
        }

        return ans;
    }
};