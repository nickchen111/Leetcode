/*
1544. Make The String Great
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string makeGood(string s) {
        int n = s.size();
        string res;
        for(int i = 0; i < n; i++){
            if(res.empty() || (!res.empty() && res.back()-32 != s[i] && res.back()+32 != s[i])){
                res.push_back(s[i]);
            }
            else res.pop_back();
        }

        return res;
       
    }
};

/*
不能大小寫相鄰
*/
