/*
792. Number of Matching Subsequences
*/

//TC:O(n*logm * k) SC:O(26*m)
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        vector<vector<int>> pos(26);

        //預處理
        for(int i = 0; i<s.size();i++){
            pos[s[i]-'a'].push_back(i);
        }

        int res = 0;
        for(auto word:words){
            if(word.size() > s.size()) continue;
            if(check(word,pos)) res++;
        }

        return res;
    }

    bool check(string& word,  vector<vector<int>> pos){
        int i =0;//每個字串都一樣從一開始開始尋找
        for(auto ch:word){
            auto iter = lower_bound(pos[ch-'a'].begin(), pos[ch-'a'].end(), i);
            if(iter == pos[ch-'a'].end()) return false;
            i = *iter+1;
        }

        return true;
    }
};

//高效預處理 by 類似DP TC:O(n*k) SC:O(26*m)
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        int m = s.size();
        s = "#" + s;
        int dp[m+1][26];
        //從最右邊往後看肯定都是沒有的
        for(int k = 0; k<26; k++){
            dp[m][k] = -1;
        }

        for(int i = m; i>=1; i--){
            for(int k = 0; k<26; k++){
                dp[i-1][k] = dp[i][k];
            }
            dp[i-1][s[i]-'a'] = i;//最近的那項更新
        }

        int res = 0;
        for(auto word:words){
            int i = 0;
            bool flag = 1;
            for(auto ch:word){
                i = dp[i][ch-'a'];
                if(i == -1){
                    flag = 0; 
                    break;
                } 
            }
            if(flag) res++;
        }

        return res;
    }
};

/*
此題為392題的follow up 如果要判斷很多個字串 
暴力解就會是 (m+n) * k n為要搜尋的字串平均長度 m為被搜尋的母字串的長度 k為要搜尋的字串數量

比較好的解法有兩種預處理的方式
1. 二分:先用線性的時間掃過要被搜尋的字串 將每個字母的位置記錄下來
TC: n*logm * k
2. 類似DP的操作 如果可以有一個數組 dp[i][ch] 告訴我從 i 往右看 哪裡有ch這個字(不包含i本身下的字)
 那就可以在O(1)的時間找到下個字
*/
