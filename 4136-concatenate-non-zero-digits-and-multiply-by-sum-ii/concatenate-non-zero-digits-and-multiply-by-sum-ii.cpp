class Solution {
public:
    const long long MOD = 1000000007LL;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<long long> prefixVal(n + 1, 0);
        vector<int> prefixCount(n + 1, 0);
        vector<long long> prefixSum(n + 1, 0);


        for (int i = 1; i <= n; i++) {
            int d = s[i - 1] - '0';
            prefixCount[i] = prefixCount[i - 1] + (d != 0 ? 1 : 0);
            prefixSum[i]   = prefixSum[i - 1] + d;

            if (d != 0)
                prefixVal[i] = (prefixVal[i - 1] * 10 + d) % MOD;
            else
                prefixVal[i] = prefixVal[i - 1];
        }


        vector<long long> pow10(n + 1);
        pow10[0] = 1;
        for (int i = 1; i <= n; i++)
            pow10[i] = (pow10[i - 1] * 10) % MOD;


        vector<int> result;
        result.reserve(queries.size());

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            int cnt = prefixCount[r + 1] - prefixCount[l];

            if (cnt == 0) {

                result.push_back(0);
                continue;
            }
            long long val = ( (prefixVal[r + 1] - (prefixVal[l] * pow10[cnt]) % MOD) % MOD + MOD ) % MOD;

            long long sum = prefixSum[r + 1] - prefixSum[l];   // actual digit sum (chota number)

            long long ans = (val * (sum % MOD)) % MOD;

            result.push_back((int)ans);
        }

        return result;
    }
};

