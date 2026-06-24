class Solution {
public:
    static const long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (!A[i][k]) continue;

                for (int j = 0; j < n; j++) {
                    if (!B[k][j]) continue;

                    C[i][j] =
                        (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();

        Matrix res(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) res[i][i] = 1;

        while (exp) {
            if (exp & 1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }

        return res;
    }

    vector<long long> multiplyVec(
        const Matrix& A,
        const vector<long long>& v
    ) {
        int n = A.size();
        vector<long long> res(n, 0);

        for (int i = 0; i < n; i++) {
            long long cur = 0;

            for (int j = 0; j < n; j++) {
                cur = (cur + A[i][j] * v[j]) % MOD;
            }

            res[i] = cur;
        }

        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int M = r - l + 1;

        int S = 2 * M;

        // state:
        // 0..M-1     => up[v]
        // M..2M-1    => down[v]

        Matrix T(S, vector<long long>(S, 0));

        for (int u = 0; u < M; u++) {

            // down[u] -> up[v] (v > u)
            for (int v = u + 1; v < M; v++) {
                T[v][M + u] = 1;
            }

            // up[u] -> down[v] (v < u)
            for (int v = 0; v < u; v++) {
                T[M + v][u] = 1;
            }
        }

        vector<long long> init(S, 0);

        // length = 2
        for (int v = 0; v < M; v++) {
            init[v] = v;              // up[v]
            init[M + v] = M - 1 - v;  // down[v]
        }

        if (n == 2) {
            long long ans = 0;
            for (auto x : init) ans = (ans + x) % MOD;
            return (int)ans;
        }

        Matrix P = power(T, n - 2);

        vector<long long> finalState = multiplyVec(P, init);

        long long ans = 0;
        for (long long x : finalState) {
            ans = (ans + x) % MOD;
        }

        return (int)ans;
    }
};