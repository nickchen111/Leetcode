/*
1400. Construct K Palindrome Strings
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool canConstruct(string s, int k) {
        int n = s.size();
        if(n < k) return false;
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++){
            map[s[i]-'a']+=1;
        }
        int count = 0;
        for(auto p:map){
            if(p.second%2 == 1) count+=1;
            if(count > k) return false;
        }

        return true;
    }
};

/*
此題問說給你一串字符串 能否組成題目規定的k個回文串 字符串內文字要全部用光
此題思考方向讓我學到有些題目正著不行就反著想 什麼樣的情況沒辦法組成要求的回文串
1. 字串長度小於k
2. odd 種類次數大於k

*/
