/*
424. Longest Repeating Character Replacement
*/

// 2025.01.26 兩種寫法 TC:O(n) / O(26*n) SC:O(1)
class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size(), ans = 0, i = 0, mx = 0; // mx會是歷史出現的最大次數的滿足條件的滑窗 所以就算縮小窗口時會是不滿足條件的 但也不影響答案
        vector<int> cnt(26);
        for(int j = 0; j < n; j++) {
            mx = max(mx, ++cnt[s[j] - 'A']);
            while(j - i + 1 - mx > k) {
                cnt[s[i++]-'A'] -= 1;
            }
            ans = max(ans, j - i + 1);
        }
        return ans;
    }
};

class Solution {
public:
    int characterReplacement(string s, int k) {
        int n = s.size(), ans = 0;
        for(char ch = 'A'; ch <= 'Z'; ch++) {
            if(s.find(ch) == string::npos) continue;
            int i = 0, cnt = 0;
            for(int j = 0; j < n; j++) {
                cnt += (s[j] != ch);
                while(cnt > k) {
                    cnt -= (s[i++] != ch);
                }
                ans = max(ans, j - i + 1);
            }
        } 
        return ans;
    }
};



//slide window TC:O(26*n) SC:O(26)
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26,0);
        int res = 0;
        int j = 0;
        for(int i =0; i<s.size(); i++){
            //checkok去確認i到j這段是否合法
            while(j < s.size() && checkOk(j,count,s,k,j-i+1)){
                j++;//繼續擴大看能否容納更多
            }
            //跳出來代表i 到 j-1為合法區段
            res = max(res, j-i);
            count[s[i]-'A']-=1;
        }
        return res;
    }
    bool checkOk(int j, vector<int>& count, string& s, int k,int total){
        count[s[j]-'A']+=1;
        int maxCount = *max_element(count.begin(),count.end());
        if(total - maxCount <= k){
            return true;
        }
        else{
            count[s[j]-'A']-=1;
            return false;
        }
    }
}

// 改固定的邊界
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> count(26,0);
        int res = 0;
        int i = 0;
        //用for循環固定其中一個邊界
        for(int j =0; j<s.size(); j++){
            count[s[j]-'A']+=1;

            while(j-i+1 - *max_element(count.begin(),count.end()) > k){
                count[s[i]-'A']-=1;
                i++;
            }
            res = max(res, j-i+1);
        }
        return res;
    }
};

// 

/*
此題是slide window 題目
slide window 的兩種思想
a. 哎個去認定26個字母會是最長的那個選擇 去盡力讓他最長
b. 直接從滑動窗口裡面挑選出當下最多的認定他為有可能達到最長的字母
確認是否合法: 當下長度-目前最多的字母 <= k
寫法轉換：改變固定的邊界 改成右邊界固定
*/
