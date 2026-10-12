class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
          const int MOD = 1e9 + 7;
        vector<int> bit(32, 0);

        for (int x : nums) {
            for (int i = 0; i < 32; i++) {
                if (x & (1 << i)) {
                    bit[i]++;
                }
            }
        }

        long long ans = 0;

        while (k--) {
            long long num = 0;

            for (int i = 0; i < 32; i++) {
                if (bit[i] > 0) {
                    num |= (1LL << i);
                    bit[i]--;
                }
            }

            ans = (ans + num * num) % MOD;
        }

        return ans;
        
    }
};