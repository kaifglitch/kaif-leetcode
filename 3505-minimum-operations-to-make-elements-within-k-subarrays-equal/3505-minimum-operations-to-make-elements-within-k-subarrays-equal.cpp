class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        auto balance = [&](int target) {
            while ((int)low.size() > target) {
                int val = *low.rbegin();
                low.erase(prev(low.end()));
                sumLow -= val;

                high.insert(val);
                sumHigh += val;
            }

            while ((int)low.size() < target && !high.empty()) {
                int val = *high.begin();
                high.erase(high.begin());
                sumHigh -= val;

                low.insert(val);
                sumLow += val;
            }
        };

        auto add = [&](int val) {
            if (low.empty() || val <= *low.rbegin()) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }
        };

        auto remove = [&](int val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }
        };

        vector<long long> cost(n - x + 1);

        // First window
        for (int i = 0; i < x; i++) {
            add(nums[i]);
            balance((i + 2) / 2);
        }

        // Calculate cost of first window
        long long median = *low.rbegin();

        cost[0] = median * low.size() - sumLow
                + sumHigh - median * high.size();

        // Sliding window
        for (int i = x; i < n; i++) {
            remove(nums[i - x]);
            balance(x / 2);

            add(nums[i]);
            balance((x + 1) / 2);

            median = *low.rbegin();

            cost[i - x + 1] =
                median * low.size() - sumLow
                + sumHigh - median * high.size();
        }

        // DP
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {

                // Skip current element
                dp[j][i] = dp[j][i - 1];

                // Select a window of size x
                if (i >= x && dp[j - 1][i - x] != INF) {
                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
        
    }
};