/*
3039. Apply Operations to Make String Empty
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    string lastNonEmptyString(string s) {
        int n = s.size();
        vector<int> count(26,0);
        for(auto x : s){
            count[x-'a'] += 1;
        }
        
        int maxVal = 0;
        for(int i = 0; i < 26; i++){
            if(count[i] > maxVal) {
                maxVal = count[i];
            }
        }
        
        string res;
        unordered_set<char> set;
        for(int i = n-1; i >= 0; i--){
            if(count[s[i]-'a'] == maxVal && set.find(s[i]) == set.end()){
                set.insert(s[i]);
                res.push_back(s[i]);
            }
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};

/*
這題讓你每次做一個操作 將這一輪中第一次出現的字母都刪掉 然後一直刪掉空為止 之前的那一步會剩下哪些字母
只要想說哪些是頻率最高的留下他們就對了 然後從後面遍歷回去 一旦遇到頻率最高的字就加入答案並且加入set中防止重複選取 最後對答案reverse
*/
