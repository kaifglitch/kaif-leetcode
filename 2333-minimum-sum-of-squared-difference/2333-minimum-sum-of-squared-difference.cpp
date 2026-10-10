class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
             vector<int> diff;
        long long k = (long long)k1 + k2;
        long long sum = 0;

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            diff.push_back(d);
            sum += d;
        }

        if (sum <= k) return 0;

        int low = 0, high = 100000;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long need = 0;

            for (int d : diff) {
                if (d > mid) {
                    need += d - mid;
                }
            }

            if (need <= k)
                high = mid;
            else
                low = mid + 1;
        }

        int level = low;
        long long used = 0;
        long long ans = 0;

        for (int d : diff) {
            if (d > level) {
                used += d - level;
                d = level;
            }
            ans += 1LL * d * d;
        }

        long long remaining = k - used;

        for (int i = 0; i < diff.size() && remaining > 0; i++) {
            if (diff[i] >= level && level > 0) {
                ans -= 1LL * level * level;
                ans += 1LL * (level - 1) * (level - 1);
                remaining--;
            }
        }

        return ans;
        
    }
};