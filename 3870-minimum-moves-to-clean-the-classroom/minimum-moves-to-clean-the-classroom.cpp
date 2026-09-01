class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        int litterCount = 0;

        vector<vector<int>> litterId(m, vector<int>(n, -1));

        // Find start and assign IDs to litter
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if (classroom[i][j] == 'L') {
                    litterId[i][j] = litterCount++;
                }
            }
        }

        // No litter
        if (litterCount == 0)
            return 0;

        int totalMasks = 1 << litterCount;
        int fullMask = totalMasks - 1;

        /*
            best[r][c][mask] =
            maximum energy with which we have reached
            (r, c) after collecting 'mask' litters.
        */

        vector<vector<vector<int>>> best(
            m,
            vector<vector<int>>(
                n,
                vector<int>(totalMasks, -1)
            )
        );

        struct State {
            int r;
            int c;
            int mask;
            int energy;
            int dist;
        };

        queue<State> q;

        best[sr][sc][0] = energy;

        q.push({
            sr,
            sc,
            0,
            energy,
            0
        });

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {

            State cur = q.front();
            q.pop();

            int r = cur.r;
            int c = cur.c;
            int mask = cur.mask;
            int en = cur.energy;
            int dist = cur.dist;

            // All litter collected
            if (mask == fullMask)
                return dist;

            // No energy -> cannot move
            if (en == 0)
                continue;

            for (int d = 0; d < 4; d++) {

                int nr = r + dr[d];
                int nc = c + dc[d];

                // Out of bounds
                if (nr < 0 || nr >= m ||
                    nc < 0 || nc >= n)
                    continue;

                // Obstacle
                if (classroom[nr][nc] == 'X')
                    continue;

                // Moving costs 1 energy
                int newEnergy = en - 1;

                int newMask = mask;

                // Collect litter
                if (classroom[nr][nc] == 'L') {
                    int id = litterId[nr][nc];
                    newMask |= (1 << id);
                }

                // Reset
                if (classroom[nr][nc] == 'R') {
                    newEnergy = energy;
                }

                /*
                    Dominance check:

                    If we have already reached this same
                    (nr, nc, newMask) with MORE or EQUAL energy,
                    then this state is useless.
                */

                if (best[nr][nc][newMask] >= newEnergy)
                    continue;

                // This is a better state
                best[nr][nc][newMask] = newEnergy;

                q.push({
                    nr,
                    nc,
                    newMask,
                    newEnergy,
                    dist + 1
                });
            }
        }

        return -1;
    }
};