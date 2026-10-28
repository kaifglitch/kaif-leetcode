class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
          int m = grid.size();
        int n = grid[0].size();

        int MAX = 1024;

        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(n, vector<bool>(MAX, false))
        );

        dp[0][0][grid[0][0]] = true;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int x = 0; x < MAX; x++) {

                    int prev = x ^ grid[i][j];

                    if (i > 0 && dp[i-1][j][prev]) {
                        dp[i][j][x] = true;
                    }

                    if (j > 0 && dp[i][j-1][prev]) {
                        dp[i][j][x] = true;
                    }
                }
            }
        }

        for (int x = 0; x < MAX; x++) {
            if (dp[m-1][n-1][x]) {
                return x;
            }
        }

        return 0;
        
    }
};