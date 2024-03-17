/*
3085. Minimum Deletions to Make String K-Special
*/

// TC:O(n + mlgm + m) SC:O(m) m = 26 n = 1e5
class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> count(26);
        vector<int> freq;
        for(auto x : word){
            count[x-'a'] += 1;
        }
        
        for(auto x : count){
            if(x != 0)
                freq.push_back(x);
        }
        
        sort(freq.begin(), freq.end());// freq small -> large
        int n = freq.size();
        vector<int> sufSum(n);
        for(int i = n-1; i >= 0; i--){
            sufSum[i] = (i+1 >= n ? 0 : sufSum[i+1]) + freq[i];
        }
        
        int res = INT_MAX;
        int cut = 0;
        int j = 0;
        
        for(int i = 0; i < n; i++){
            while(j < n && freq[j] - freq[i] <= k){
                j++;
            }
            
            res = min(res, cut + (j==n ? 0 : sufSum[j]) - (freq[i]+k)*(n-j));
            cut += freq[i];
        }
        
        
        
        return res;
        
    }
};

/*
|freq(word[i]) - freq(word[j])| <= k
只有包含小寫字母 問最少需要刪除幾個字
最多跟最少的差不能太大
dabdcbdcdcd -> a:1 b:2 c:3 d:5 k = 2
看最大跟最少freq是多少 刪除誰效益最高 會發現難以判斷到底現在該刪除哪個比較好
所以從最小的數字 每個數字都去試試看 去維護一個當下index i 到 j-1 都符合 freq[i] - freq[j] <= k 然後去看如果這個字不刪除
其他較大數字要刪除需要花費多少次數 一個一個去嘗試 找最小次數 

*/
