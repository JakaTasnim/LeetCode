class Solution {
public:
    static const int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        vector<int> up(m), down(m);
        vector<int> nup(m), ndown(m);
        vector<int> pre(m + 1), suf(m + 1);

        // length = 2
        for (int i = 0; i < m; i++) {
            up[i] = i;
            down[i] = m - i - 1;
        }

        for (int len = 3; len <= n; len++) {

            pre[0] = 0;
            for (int i = 0; i < m; i++)
                pre[i + 1] = (pre[i] + down[i]) % MOD;

            suf[m] = 0;
            for (int i = m - 1; i >= 0; i--)
                suf[i] = (suf[i + 1] + up[i]) % MOD;

            for (int i = 0; i < m; i++) {
                nup[i] = pre[i];
                ndown[i] = suf[i + 1];
            }

            up.swap(nup);
            down.swap(ndown);
        }

        long long ans = 0;

        for (int i = 0; i < m; i++) {
            ans += up[i];
            ans += down[i];
            ans %= MOD;
        }

        return ans;
    }
};