class Solution {
    struct Node {
        int product = 1;
        array<int, 5> prefix{};
    };

    int n, mod;
    vector<Node> tree;

    Node makeLeaf(int value) {
        Node leaf;
        leaf.product = value % mod;

        // Single element ka exactly one non-empty prefix hai.
        leaf.prefix[leaf.product] = 1;

        return leaf;
    }

    Node merge(const Node& a, const Node& b) {
        Node result;
        result.product = (a.product * b.product) % mod;

        // Prefixes entirely inside the left segment.
        result.prefix = a.prefix;

        // Complete left segment + a prefix of the right segment.
        for (int r = 0; r < mod; ++r) {
            int newRemainder = (a.product * r) % mod;
            result.prefix[newRemainder] += b.prefix[r];
        }

        return result;
    }

    void build(int node, int left, int right,
               const vector<int>& nums) {
        if (left == right) {
            tree[node] = makeLeaf(nums[left]);
            return;
        }

        int mid = left + (right - left) / 2;

        build(node * 2, left, mid, nums);
        build(node * 2 + 1, mid + 1, right, nums);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int left, int right,
                int index, int value) {
        if (left == right) {
            tree[node] = makeLeaf(value);
            return;
        }

        int mid = left + (right - left) / 2;

        if (index <= mid) {
            update(node * 2, left, mid, index, value);
        } else {
            update(node * 2 + 1, mid + 1, right, index, value);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    // Returns information for [start, right] within this node.
    Node querySuffix(int node, int left, int right, int start) {
        if (start <= left) {
            return tree[node];
        }

        int mid = left + (right - left) / 2;

        // Required suffix is completely inside the right child.
        if (start > mid) {
            return querySuffix(
                node * 2 + 1, mid + 1, right, start
            );
        }

        // Required suffix = part of left child + entire right child.
        Node leftPart = querySuffix(
            node * 2, left, mid, start
        );

        return merge(leftPart, tree[node * 2 + 1]);
    }

public:
    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        n = nums.size();
        mod = k;

        tree.assign(4 * n, Node{});
        build(1, 0, n - 1, nums);

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            // This update persists for subsequent queries.
            update(1, 0, n - 1, q[0], q[1]);

            // Get prefix counts of nums[start ... n - 1].
            Node suffix = querySuffix(1, 0, n - 1, q[2]);

            answer.push_back(suffix.prefix[q[3]]);
        }

        return answer;
    }
};