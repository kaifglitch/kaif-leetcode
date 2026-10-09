class Solution {
public:
    int minInsertions(string s) {
        int open =0 ;
        int ans = 0 ;
        for (int i = 0; i < s.length(); i++){
            if(s[i] == '('){
                open++;
                if(open < 0 && i+1 < s.length() && s[i+1] == '(' ){
                    ans++;

                }
            }
            else{
                if( i+1 < s.length() && s[i+1] == ')'){
                    if(open > 0){
                        open--;
                    }
                    else{
                        ans++;
                    }
                    i++;
                }
                else{
                    ans++;
                    if(open > 0){
                        open--;
                    }else{
                        ans++;
                    }
                }
            }
        }
     ans += open *2;
     return ans;
        
    }
};