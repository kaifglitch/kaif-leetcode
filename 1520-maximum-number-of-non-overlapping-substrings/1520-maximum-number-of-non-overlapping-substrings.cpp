class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
          int n = s.size();
        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int x = s[i] - 'a';

            first[x] = min(first[x], i);
            last[x] = i;
        }

        vector<pair<int, int>> intervals;
        for (int c = 0; c < 26; c++) {

            if (last[c] == -1)
                continue;

            int start = first[c];
            int end = last[c];

            bool valid = true;

            for (int i = start; i <= end; i++) {

                int x = s[i] - 'a';
                if (first[x] < start) {
                    valid = false;
                    break;
                }
                end = max(end, last[x]);
            }

            if (valid) {
                intervals.push_back({start, end});
            }
        }
        sort(intervals.begin(), intervals.end(),
             [](pair<int,int> a, pair<int,int> b) {
                 return a.second < b.second;
             });

        vector<string> ans;

        int prevEnd = -1;
        for (auto it : intervals) {

            int start = it.first;
            int end = it.second;

            if (start > prevEnd) {

                ans.push_back(s.substr(start, end - start + 1));

                prevEnd = end;
            }
        }

        return ans;
        
    }
};