class Solution {
public:
    using ll = long long;

    struct Node {
        ll val;
        int l, r;

        bool operator<(const Node &other) const {
            return val < other.val;
        }
    };

    vector<int> lg;
    vector<vector<int>> mx, mn;

    int getMax(int l, int r) {
        int j = lg[r - l + 1];
        return max(mx[j][l], mx[j][r - (1 << j) + 1]);
    }

    int getMin(int l, int r) {
        int j = lg[r - l + 1];
        return min(mn[j][l], mn[j][r - (1 << j) + 1]);
    }

    long long value(int l, int r) {
        return 1LL * getMax(l, r) - getMin(l, r);
    }

    long long maxTotalValue(vector<int>& nums, int k) {

        int n = nums.size();

        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        int K = lg[n] + 1;

        mx.assign(K, vector<int>(n));
        mn.assign(K, vector<int>(n));

        for (int i = 0; i < n; i++) {
            mx[0][i] = nums[i];
            mn[0][i] = nums[i];
        }

        for (int j = 1; j < K; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                mx[j][i] = max(mx[j - 1][i],
                               mx[j - 1][i + (1 << (j - 1))]);

                mn[j][i] = min(mn[j - 1][i],
                               mn[j - 1][i + (1 << (j - 1))]);
            }
        }

        priority_queue<Node> pq;

        for (int l = 0; l < n; l++) {
            pq.push({value(l, n - 1), l, n - 1});
        }

        long long ans = 0;

        while (k--) {
            Node cur = pq.top();
            pq.pop();

            ans += cur.val;

            if (cur.r > cur.l) {
                pq.push({value(cur.l, cur.r - 1),
                         cur.l,
                         cur.r - 1});
            }
        }

        return ans;
    }
};