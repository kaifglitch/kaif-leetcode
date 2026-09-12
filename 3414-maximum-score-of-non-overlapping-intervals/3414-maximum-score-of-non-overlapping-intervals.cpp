class Solution {
public:
       struct Node {
        long long score;
        vector<int> ids;
    };

    vector<vector<Node>> dp;
    vector<vector<int>> a;

    Node solve(int i, int k) {
        if (i >= a.size() || k == 0) {
            return {0, {}};
        }

        if (dp[i][k].score != -1) {
            return dp[i][k];
        }
        Node skip = solve(i + 1, k);

        int l = a[i][0];
        int r = a[i][1];
        int w = a[i][2];
        int originalIndex = a[i][3];

        int low = i + 1;
        int high = a.size();

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (a[mid][0] > r)
                high = mid;
            else
                low = mid + 1;
        }

        int next = low;

        Node take = solve(next, k - 1);

        take.score += w;
        take.ids.push_back(originalIndex);

        sort(take.ids.begin(), take.ids.end());

        if (take.score > skip.score) {
            return dp[i][k] = take;
        }

        if (take.score < skip.score) {
            return dp[i][k] = skip;
        }
        if (take.ids < skip.ids) {
            return dp[i][k] = take;
        }

        return dp[i][k] = skip;
    }
    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();
        a.clear();

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }
        sort(a.begin(), a.end());
        dp.assign(n, vector<Node>(5, {-1, {}}));

        return solve(0, 4).ids;
        
    }
};