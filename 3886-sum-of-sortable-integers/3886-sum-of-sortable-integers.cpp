class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
           int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {

            if (n % k != 0) continue;

            bool valid = true;
            int prevMax = INT_MIN;

            for (int i = 0; i < n; i += k) {

                int mn = INT_MAX;
                int mx = INT_MIN;
                int desc = 0;

                for (int j = 0; j < k; j++) {
                    int idx = i + j;

                    mn = min(mn, nums[idx]);
                    mx = max(mx, nums[idx]);

                    int next = i + (j + 1) % k;

                    if (nums[idx] > nums[next]) {
                        desc++;
                    }
                }

                if (desc > 1) {
                    valid = false;
                    break;
                }

                if (prevMax > mn) {
                    valid = false;
                    break;
                }

                prevMax = mx;
            }

            if (valid) {
                ans += k;
            }
        }

        return ans;
        
    }
};