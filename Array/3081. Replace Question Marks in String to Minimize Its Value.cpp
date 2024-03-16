/*
3081. Replace Question Marks in String to Minimize Its Value
*/


// TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    string minimizeStringValue(string s) {
        int n = s.size();
        vector<vector<int>> presum(n, vector<int>(26));
        vector<vector<int>> suffix(n, vector<int>(26));
        vector<int> count(26);
        vector<int> tmp(26); // 記錄在過程中會加入的字母
        vector<int> pos; // 問號都在哪些位置
        for(int i = 0; i < n; i++){
            for(int j = 0; j < 26; j++){
                presum[i][j] += count[j];
            }
            if(s[i] >= 'a' && s[i] <= 'z'){
                count[s[i]-'a'] += 1;
            }
            else pos.push_back(i);
        }
        
        for(int i = 0; i < 26; i++){
            count[i] = 0;
        }
        
        for(int i = n-1; i >= 0; i--){
            for(int j = 0; j < 26; j++){
                suffix[i][j] += count[j];
            }
            if(s[i] >= 'a' && s[i] <= 'z'){
                count[s[i]-'a'] += 1;
            }
            
        }
        
        string res = "";
        string need = "";
        for(int i = 0; i < n; i++){
            if(s[i] >= 'a' && s[i] <= 'z'){
                res += s[i];
            }
            else {
                int minVal = INT_MAX/2;
                char ch;
                for(int j = 0; j < 26; j++){
                    int cur = presum[i][j] + suffix[i][j] + tmp[j];
                    if(cur < minVal){
                        ch = 'a' + j;
                        minVal = cur;
                    }
                }
                
                tmp[ch-'a'] += 1;
                res += ' ';
                need += ch;
            }
        }
        sort(need.begin(), need.end());
        
        for(int i = 0; i < pos.size(); i++){
            res[count2[i]] = need[i];
        }
        
        return res;
        
    }
};


/*
定義一個函式 他可以去看前面有多少個當前的字母 就可以去加上那個數量的val(不包含自己)
然後給你一個字串 s 裡面有問號可以任意填字母 問說可以達成他的最小cost的情況下 他會是什麼字串
也就是每次看到一個？我會想知道他後面有多少個a-z 前面有多少個a-z 我會挑最少的狀況去填充 貪心
如果有很多答案 要回傳字典序最小的那個
走每一步的時候我都要瞻前顧後 判斷一下當前的數量 然後去找出最小的元素  並且還要去預測後面的元素可以填什麼
"abcdefghijklmnopqrstuvwxy??"
根據上面的例子會發現並不是每次填入都填最佳的最好 仍然有可能先填次佳的 但到最後按照分數會變得一樣
所以要是貪心的把每次問號可以填入的字母做排序 然後按照字典序從左到右塞入
*/
