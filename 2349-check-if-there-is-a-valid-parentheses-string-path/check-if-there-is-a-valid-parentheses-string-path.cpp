class Solution {
    int m, n;
    vector<vector<vector<int>>> memo;

    bool dfs(int row, int col, int balance, vector<vector<char>>& grid) {

        if (row >= m || col >= n) {
            return false;
        }

        int& result = memo[row][col][balance];

        if (result != -1) {
            return result;
        }

        // Include the current cell.
        int newBalance = balance + (grid[row][col] == '(' ? 1 : -1);

        // Number of cells still to visit after this cell.
        int remaining = (m - 1 - row) + (n - 1 - col);

        if (newBalance < 0 || newBalance > remaining) {
            return result = 0;
        }

        if (row == m - 1 && col == n - 1) {
            return result = (newBalance == 0);
        }

        // Try moving down or right.
        result = dfs(row + 1, col, newBalance, grid) ||
                 dfs(row, col + 1, newBalance, grid);

        return result;
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        int pathLength = m + n - 1;

        if (grid[0][0] == ')' ||
            grid[m - 1][n - 1] == '(' ||
            pathLength % 2 != 0) {
            return false;
        }

        memo.assign(
            m,
            vector<vector<int>>(
                n,
                vector<int>(pathLength + 1, -1)
            )
        );

        return dfs(0, 0, 0, grid);
    }
};