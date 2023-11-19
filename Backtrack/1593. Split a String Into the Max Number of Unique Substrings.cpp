/*
1593. Split a String Into the Max Number of Unique Substrings
*/

// general backtrack TC:O(2^n) SC:O(2^n)
class Solution {
    int res = INT_MIN;
    unordered_set<string> set;
public:
    int maxUniqueSplit(string s) {
        
        backtrack(s,0,0);

        return res;
    }
    void backtrack(string& s, int cur, int count){
        if(cur == s.size()){
            res = max(res,count);
            return;
        }
        
        for(int i = cur; i<s.size(); i++){
            string curStr = s.substr(cur,i-cur+1);
            if(set.find(curStr) != set.end()) continue;
            set.insert(curStr);
            backtrack(s,i+1,count+1);
            set.erase(curStr);
        }
    }
};

//優化 
class Solution {
    int res = 0;
    unordered_set<string> set;
public:
    int maxUniqueSplit(string s) {
        
        backtrack(s,0,0);

        return res;
    }
    void backtrack(string& s, int cur, int count){
        if(cur == s.size()){
            res = max(res,count);
            return;
        }
        //小優化 如果split後剩下的字元數分別當作字串加上目前字串數目都沒有之前的結果多 直接return
        if(count + s.size() - cur <= res) return;

        for(int i = cur; i<s.size(); i++){
            string curStr = s.substr(cur,i-cur+1);
            if(set.find(curStr) == set.end()){
                set.insert(curStr);
                backtrack(s,i+1,count+1);
                set.erase(curStr);
            }
        }
    }
};
