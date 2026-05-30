class SegmentTree {
public:
    int n;
    vector<int> tree;

    SegmentTree(int n) : n(n) {
        tree.resize(4 * n, 0);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;

        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);

        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l)
            return 0;

        if (l <= start && end <= r)
            return tree[node];

        int mid = (start + end) / 2;

        return max(
            query(2 * node, start, mid, l, r),
            query(2 * node + 1, mid + 1, end, l, r)
        );
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query(1, 0, n - 1, l, r);
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {

        int MX = 50000;

        set<int> pos;
        pos.insert(0);
        pos.insert(MX);

        vector<bool> removed(50001, false);

        for (auto &q : queries) {
            if (q[0] == 1) {
                pos.insert(q[1]);
                removed[q[1]] = true;
            }
        }

        SegmentTree seg(MX + 1);

        auto updateGap = [&](int right, int gap) {
            seg.update(right, gap);
        };

        for (auto it = next(pos.begin()); it != pos.end(); ++it) {
            auto prv = prev(it);
            updateGap(*it, *it - *prv);
        }

        vector<bool> ans;

        for (int i = (int)queries.size() - 1; i >= 0; i--) {

            auto &q = queries[i];

            if (q[0] == 1) {

                int x = q[1];

                auto it = pos.find(x);

                auto L = prev(it);
                auto R = next(it);

                updateGap(*R, *R - *L);

                pos.erase(it);
            }
            else {

                int x = q[1];
                int sz = q[2];

                auto it = pos.upper_bound(x);

                int rightObs = *it;
                int leftObs = *prev(it);

                int best = seg.query(0, x);

                best = max(best, x - leftObs);

                ans.push_back(best >= sz);
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};