/*
2981. Find Longest Special Substring That Occurs Thrice I
*/
  
// TC:O(n^2) SC:O(n^2) Brute Force
class Solution {
public:
    int maximumLength(string s) {
        int n = s.size();
        unordered_map<string, int> map;
        for(int i = 0; i < n; i++){
            unordered_map<char, int> mp;
            for(int j = i; j < n; j++){
                mp[s[j]] += 1;
                if(mp.size() == 1)
                    map[s.substr(i,j-i+1)] += 1;
                else break;
            }
        }

        int res = 0;
        for(auto &p : map){
            if(p.first.size() > res && p.second >= 3){
                res = p.first.size();
            }
        }
        
        return res == 0 ? -1 : res;
    }
};

/*
規定一個字串要滿足
1. 只有他自己一個字
2. 字串要重複出現至少3次 
這樣的字最長會是多長 沒有的話返回-1
*/
