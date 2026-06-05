class Solution {
public:
    struct Node {
        long long cnt;
        long long wav;
    };

    string s;
    Node dp[20][12][12][2];
    bool vis[20][12][12][2];

    Node dfs(int pos, int prev1, int prev2, bool started, bool tight) {

        if (pos == s.size()) {
            return {1, 0};
        }

        if (!tight && vis[pos][prev1][prev2][started])
            return dp[pos][prev1][prev2][started];

        int lim = tight ? s[pos] - '0' : 9;

        Node res = {0, 0};

        for (int d = 0; d <= lim; d++) {

            bool ntight = tight && (d == lim);

            if (!started && d == 0) {

                Node child =
                    dfs(pos + 1, 10, 10, false, ntight);

                res.cnt += child.cnt;
                res.wav += child.wav;
            }
            else {

                if (!started) {

                    Node child =
                        dfs(pos + 1, d, 10, true, ntight);

                    res.cnt += child.cnt;
                    res.wav += child.wav;
                }
                else {

                    int add = 0;

                    if (prev2 != 10) {

                        if ((prev1 > prev2 && prev1 > d) ||
                            (prev1 < prev2 && prev1 < d))
                            add = 1;
                    }

                    Node child =
                        dfs(pos + 1, d, prev1, true, ntight);

                    res.cnt += child.cnt;
                    res.wav += child.wav +
                               1LL * add * child.cnt;
                }
            }
        }

        if (!tight) {
            vis[pos][prev1][prev2][started] = true;
            dp[pos][prev1][prev2][started] = res;
        }

        return res;
    }

    long long solve(long long x) {

        if (x <= 0) return 0;

        s = to_string(x);

        memset(vis, 0, sizeof(vis));

        return dfs(0, 10, 10, false, true).wav;
    }

    long long totalWaviness(long long num1, long long num2) {

        return solve(num2) - solve(num1 - 1);
    }
};