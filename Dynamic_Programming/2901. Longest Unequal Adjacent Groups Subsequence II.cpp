/*
2901. Longest Unequal Adjacent Groups Subsequence II
*/

// TC:O(n*n*10) SC:O(n*n*10)
class Solution {
    int calculate(string& a, string& b){
        int count = 0;
        for(int i = 0; i < a.size(); i++){
            if(a[i] != b[i]) count += 1;
            if(count > 1) break;
        }

        return count;
    }
public:
    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        vector<vector<string>> dp(n);
        //自己要先有自己
        for(int i = 0; i < n; i++){
            dp[i].push_back(words[i]);
        }

        int maxLen = 1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(groups[i] != groups[j] && words[i].size() == words[j].size()){
                    int hamDist = calculate(words[i], words[j]);
                    if(hamDist == 1){
                        if(dp[j].size() + 1 > dp[i].size()){
                            dp[i] = dp[j];
                            dp[i].push_back(words[i]);
                            maxLen = max(maxLen, (int)dp[i].size());
                        }
                    }
                }
            }
        }

        vector<string> res;
        for(int i = 0; i < n; i++){
            if(dp[i].size() == maxLen){
                res = dp[i];
                break;
            }
        }

        return res;
    }
};

/*
這題要你找任意的答案滿足三個條件 但要是最長的subsequence
1. 找到的兩個字串 他們只能有 1個不同
2. 你選擇的group 標記的數字要不同
3. 你選擇的兩個字串要相同長度
grouplen = wordlen = n <= 1000
每個字的長度最多10
x x x  | y y y | z z z 
這三區要挑最長子序列 他們長度一樣長 並且只有一個字不同
group -> len -> 只差一個字母
cab -> aab這個不一定挑了是好事 -> aab -> bab ->
string[n] 走到n為止 他最長的子序列會是多少
10^3*10*3*10 = 10^7 免強可以過
*/
