struct Block {
    int start;
    int end;
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade (string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        for (char c : s) {
            if (c == '1') total_ones++;
        }

        // 1. Extract all contiguous blocks of '1's
        vector<Block> blocks;
        for (int i = 0; i < n; ) {
            if (s[i] == '1') {
                int j = i;
                while (j < n && s[j] == '1') j++;
                blocks.push_back({i, j - 1});
                i = j;
            } else {
                i++;
            }
        }

        int k = blocks.size();
        if (k == 0) {
            return vector<int>(queries.size(), 0);
        }

        // 2. Precalculate C1 array for internal blocks
        // C1[m] = (i_m - j_m - 2) - j_{m-1} + i_{m+1}
        const int INF = 2e9;
        vector<long long> C1(k);
        for (int m = 0; m < k; ++m) {
            long long i_m = blocks[m].start;
            long long j_m = blocks[m].end;
            long long j_prev = (m > 0) ? blocks[m - 1].end : -INF;
            long long i_next = (m + 1 < k) ? blocks[m + 1].start : INF;

            C1[m] = (i_m - j_m - 2) - j_prev + i_next;
        }

        // 3. Build Sparse Table for Range Maximum Query on C1
        int max_log = 0;
        while ((1 << max_log) <= k) max_log++;
        vector<vector<long long>> st(max_log, vector<long long>(k));

        for (int i = 0; i < k; ++i) {
            st[0][i] = C1[i];
        }

        for (int j = 1; j < max_log; ++j) {
            for (int i = 0; i + (1 << j) <= k; ++i) {
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }

        auto query_st = [&](int L, int R) -> long long {
            if (L > R) return -INF;
            int j = 31 - __builtin_clz(R - L + 1);
            return max(st[j][L], st[j][R - (1 << j) + 1]);
        };

        // Helper to calculate precise gain for boundary blocks
        auto calc_gain = [&](int m, long long l, long long r) -> long long {
            long long i_m = blocks[m].start;
            long long j_m = blocks[m].end;
            long long j_prev = (m > 0) ? blocks[m - 1].end : -INF;
            long long i_next = (m + 1 < k) ? blocks[m + 1].start : INF;

            long long left_bound = max(j_prev, l - 1);
            long long right_bound = min(i_next, r + 1);

            return (i_m - j_m - 2) - left_bound + right_bound;
        };

        // 4. Process each query
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            // Find first block starting strictly after l
            int a_prime = k;
            int low = 0, high = k - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (blocks[mid].start > l) {
                    a_prime = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            // Find last block ending strictly before r
            int b_prime = -1;
            low = 0; high = k - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (blocks[mid].end < r) {
                    b_prime = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            long long max_gain = 0;

            if (a_prime <= b_prime) {
                // Check boundary block a_prime
                max_gain = max(max_gain, calc_gain(a_prime, l, r));
                
                // Check boundary block b_prime
                max_gain = max(max_gain, calc_gain(b_prime, l, r));

                // Check internal blocks strictly between a_prime and b_prime
                if (a_prime + 1 <= b_prime - 1) {
                    max_gain = max(max_gain, query_st(a_prime + 1, b_prime - 1));
                }
            }

            ans.push_back(total_ones + max_gain);
        }

        return ans;
    }
};
