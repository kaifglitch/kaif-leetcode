class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
         vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            
            num %= k;

            vector<long long> next(k, 0);

            next[num]++;

            for (int r = 0; r < k; r++) {
                int newR = (r * num) % k;
                next[newR] += dp[r];
            }

            for (int r = 0; r < k; r++) {
                ans[r] += next[r];
            }

            dp = next;
        }

        return ans;
        
    }
};