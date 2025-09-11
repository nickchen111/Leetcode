class Solution {
public:
    string sortVowels(string s) {
        int n = s.size();
        vector<char> table;
        for(int i =0; i<n; i++){
            if(string("aeiouAEIOU").find(s[i]) != string::npos){
                table.push_back(s[i]);
            }
        }

        sort(table.begin(),table.end(),greater<char>());
        string res;
        for(int i =0; i<n; i++){
            if(string("aeiouAEIOU").find(s[i]) != string::npos){
                res+=table.back();
                table.pop_back();
            }
            else res+=s[i];
        }

        return res;

    }
};