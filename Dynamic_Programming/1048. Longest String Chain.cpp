/*
1048. Longest String Chain
*/

// TC:O(nlgn + n*k) SC:O(n)
class Solution {
    static bool cmp(string& a, string& b){
        return a.size() < b.size();
    }
public:
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), cmp);
        
        unordered_map<string,int> dp;
        int max_chain = 0;
        for(const auto &word:words){
            dp[word] =1;//從這個字為出發點開始構築
            for(int i = 0; i < word.size(); i++){
                string cur = word.substr(0,i) + word.substr(i+1);//每次都忽略一個字元
                if(dp.find(cur) != dp.end()){
                    dp[word] = max(dp[word], dp[cur]+1);
                } 
            }
            max_chain = max(max_chain, dp[word]);
        }

        return max_chain;
    }
};


