class Solution {
public:
    bool isPalindrome(string s) {
       string temp ="";
    for(char c : s){
        if(isalnum(c)){
            temp += tolower(c);

        }

    }
    int n = temp.size();
    for(int i = 0; i < n/2; i++){
        if(temp[i] != temp[n-1-i]){
            return false;
        }
    }
    return true ;
    }
};