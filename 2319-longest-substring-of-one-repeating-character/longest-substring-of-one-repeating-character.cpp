class Solution {
public:

    struct Node {
        int len;
        int left;
        int right;
        int best;
        char lc;
        char rc;

        Node() {
            len = 0;
            left = 0;
            right = 0;
            best = 0;
            lc = rc = '#';
        }
    };

    vector<Node> tree;

    Node merge(Node a, Node b) {

        if (a.len == 0)
            return b;

        if (b.len == 0)
            return a;

        Node res;

        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        // Initially take maximum from both sides
        res.left = a.left;
        res.right = b.right;

        res.best = max(a.best, b.best);

        // If ending character of left segment
        // equals starting character of right segment
        if (a.rc == b.lc) {

            // Entire left segment has same character
            if (a.left == a.len) {
                res.left = a.len + b.left;
            }

            // Entire right segment has same character
            if (b.right == b.len) {
                res.right = b.len + a.right;
            }

            // Join right run of a + left run of b
            res.best = max(res.best, a.right + b.left);
        }

        return res;
    }

    void build(int node, int l, int r, string &s) {

        if (l == r) {

            tree[node].len = 1;
            tree[node].left = 1;
            tree[node].right = 1;
            tree[node].best = 1;
            tree[node].lc = s[l];
            tree[node].rc = s[l];

            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char ch) {

        if (l == r) {

            tree[node].len = 1;
            tree[node].left = 1;
            tree[node].right = 1;
            tree[node].best = 1;
            tree[node].lc = ch;
            tree[node].rc = ch;

            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, ch);
        }
        else {
            update(node * 2 + 1, mid + 1, r, idx, ch);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters,vector<int>& queryIndices) {

        int n = s.size();
        int k = queryCharacters.size();

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < k; i++) {

            int idx = queryIndices[i];
            char ch = queryCharacters[i];

            // Update string
            s[idx] = ch;

            // Update segment tree
            update(1, 0, n - 1, idx, ch);

            // Root contains answer for complete string
            ans.push_back(tree[1].best);
        }

        return ans;
    }
};