class Solution {
    static constexpr long long MOD = 1000000007;

    long long power(long long base, long long exponent) {
        long long result = 1;

        while (exponent > 0) {
            if (exponent & 1) {
                result = result * base % MOD;
            }

            base = base * base % MOD;
            exponent >>= 1;
        }

        return result;
    }

public:
    int numberOfSets(int n, int k) {
        int total = n + k - 1;
        int choose = 2 * k;

        long long numerator = 1;
        long long denominator = 1;

        // C(total, choose)
        for (int i = 1; i <= choose; ++i) {
            numerator = numerator * (total - choose + i) % MOD;
            denominator = denominator * i % MOD;
        }

        // Modular inverse using Fermat's little theorem.
        long long inverse = power(denominator, MOD - 2);

        return numerator * inverse % MOD;
    }
};