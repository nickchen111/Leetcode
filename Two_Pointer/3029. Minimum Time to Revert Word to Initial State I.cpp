/*
3029. Minimum Time to Revert Word to Initial State I
*/

// TC:O(n^2) SC:O(1)
class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        int res = INT_MAX;
        for(int i = k; i < n; i+=k){
            
            int left = 0, right = i; 
            if(n-1-i > i) continue;
            while(right < n){
                if(word[left] == word[right]) {
                    left++;
                    right++;
                }
                else break;
            }
            if(right == n) res = min(res, i/k);
        }
        
        if(n % k == 0) res = min(res, n/k);
        else res = min(res, n/k+1);
        
        return res;
        
    }
};

/*
每次都要從前面移除元素k格然後加入k個 問說最少移動幾次能讓字串變得跟之前一樣
次佳解是用two pointer在每個能斷點的地方不斷check後面的都等於前面的 n^2
(n - dp[i]) % k == 0
(n - dp[i]) % k + (n-i-1);
"abcbabcbc" k = 2 -> cbabcbcab -> abcbc (abcb) -> cbc(abcbab) -> c (aabcbabc) 多一次
"baba"
"abab"
*/
