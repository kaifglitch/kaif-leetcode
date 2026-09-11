class Solution {
public:
   vector<string> ans;
        string letters[10] = 
        { "","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        void solve (string digits, int index, string temp){
            if(index == digits.size()){
                ans.push_back(temp);
                return;
            }

            string s = letters[digits[index] - '0'];
             for (char ch : s) {

            // Add one letter
            temp += ch;

            // Move to next digit
            solve(digits, index + 1, temp);

            // Remove last letter
            temp.pop_back();
             }
        }
    vector<string> letterCombinations(string digits) {
       if (digits.empty())
            return {};

        solve(digits, 0, "");

        return ans;
        
    }
};