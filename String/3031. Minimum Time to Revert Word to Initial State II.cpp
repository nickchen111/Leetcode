/*
3031. Minimum Time to Revert Word to Initial State II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        vector<int> dp(n);
        dp[0] = 0;
        for(int i = 1; i < n; i++){
            int j = dp[i-1];
            while(j > 0 && word[i] != word[j]){
                j = dp[j-1];
            }
            dp[i] = j + (word[i] == word[j]);
        }
        
        int res = INT_MAX;
        int len = dp[n-1];
        while(len){
            if((n-len) % k != 0){
                len = dp[len-1];
            }
            else {
                res = min(res, (n-len) / k);
                break;
            }
        }

        if(res == INT_MAX){
            if(n % k == 0) res = n / k;
            else res = n/k+1;
        }

        return res;
    }
};

/*
每次都要從前面移除元素k格然後加入k個 問說最少移動幾次能讓字串變得跟之前一樣

我的想法是KMP來看頭尾符合程度找一個index+1會可以被k整除的最前面的數字
做完後從後面開始挑 挑到能夠被k整除的最大相對位置 但如果最長的前後綴不行的話 就要考慮第二長的前後綴相等狀況 這題的考點就是在考這個要怎麼求出
其實就是當前的最長前後綴數組的長度所在位置就會是可以構成第二長的前後綴相等狀況以此一直往後走
次佳解是用two pointer在每個能斷點的地方不斷check後面的都等於前面的 n^2
*/

