class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });

        vector<int> val(n);
        vector<int> posInSorted(n);
        for (int i = 0; i < n; i++) {
            val[i] = nums[order[i]];
            posInSorted[order[i]] = i;
        }
        vector<int> R(n);
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j < i) j = i;
            while (j + 1 < n && val[j + 1] - val[i] <= maxDiff) j++;
            R[i] = j;
        }
        vector<int> comp(n);
        int c = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (val[i] - val[i - 1] > maxDiff) c++;
            comp[i] = c;
        }
        int LOG = 1;
        while ((1 << LOG) < n) LOG++;
        LOG++; 

        vector<vector<int>> up(LOG, vector<int>(n));
        up[0] = R;
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }
        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int u = q[0], v = q[1];
            int pu = posInSorted[u], pv = posInSorted[v];

            if (pu == pv) {
                ans.push_back(0);
                continue;
            }
            if (comp[pu] != comp[pv]) {
                ans.push_back(-1);
                continue;
            }

            int a = min(pu, pv), b = max(pu, pv);
            int cur = a;
            long long steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < b) {
                    steps += (1LL << k);
                    cur = up[k][cur];
                }
            }
            steps += 1;

            ans.push_back((int)steps);
        }

        return ans; 
    }
};