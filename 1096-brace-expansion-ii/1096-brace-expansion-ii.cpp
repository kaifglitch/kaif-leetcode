class Solution {
public:
    vector<string> braceExpansionII(string expression) {
         set<string> ans;
        
        function<set<string>(int&)> solve = [&](int &i) {
            
            set<string> result;
            vector<string> current = {""};

            while (i < expression.size() && expression[i] != '}') {
             
                if (expression[i] == '{') {
                    i++;  

                    set<string> inside = solve(i);

                    i++;  

                    vector<string> temp;

                    for (string a : current) {
                        for (string b : inside) {
                            temp.push_back(a + b);
                        }
                    }

                    current = temp;
                }
   
                else if (expression[i] == ',') {
                    
                    for (string s : current) {
                        result.insert(s);
                    }

                    current = {""};
                    i++;
                }

                else {
                    
                    char c = expression[i];
                    i++;

                    for (string &s : current) {
                        s += c;
                    }
                }
            }

            for (string s : current) {
                result.insert(s);
            }

            return result;
        };

        int i = 0;

        set<string> result = solve(i);

        return vector<string>(result.begin(), result.end());
        
    }
};