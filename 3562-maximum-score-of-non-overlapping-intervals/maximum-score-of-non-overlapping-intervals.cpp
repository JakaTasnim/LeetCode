class Solution {
    struct State {
        long long score = 0;
        vector<int> indices;
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<int, 4>> sorted;

        for (int i = 0; i < n; ++i) {
            sorted.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(sorted.begin(), sorted.end());

        vector<int> starts(n), next(n);

        for (int i = 0; i < n; ++i) {
            starts[i] = sorted[i][0];
        }

        for (int i = 0; i < n; ++i) {
            next[i] = upper_bound(
                starts.begin(), starts.end(), sorted[i][1]
            ) - starts.begin();
        }

        vector<array<State, 5>> dp(n + 1);

        for (int i = n - 1; i >= 0; --i) {
            for (int k = 1; k <= 4; ++k) {
                State take = dp[next[i]][k - 1];
                take.score += sorted[i][2];

                int originalIndex = sorted[i][3];
                auto position = lower_bound(
                    take.indices.begin(),
                    take.indices.end(),
                    originalIndex
                );
                take.indices.insert(position, originalIndex);

                const State& skip = dp[i + 1][k];

                if (take.score > skip.score ||
                    (take.score == skip.score &&
                     take.indices < skip.indices)) {
                    dp[i][k] = take;
                } else {
                    dp[i][k] = skip;
                }
            }
        }

        return dp[0][4].indices;
    }
};

