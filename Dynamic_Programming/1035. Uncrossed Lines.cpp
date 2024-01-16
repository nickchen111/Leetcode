/*
1035. Uncrossed Lines
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        
        
        nums1.insert(nums1.begin(), -1);
        nums2.insert(nums2.begin(), -1);
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        int res = 0;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= n; j++){
                if(nums1[i] == nums2[j]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
               
            }
        }

        return dp[m][n];
    }
};

/*
給你兩個數組 將相同數字的點連接起來 並且每個數字只能連接一條線 問說 可以做出幾種不交疊的線
1. 原本的想法是two pointer 固定某一個數組不斷找另一個數組相同數字往下走 但如果在一開始就出現一個數字必須連到很後面的index
那麼他就限制了後面數字的選擇了 後面數字說不定可以連更多條線 
2. 再來想到這題如果在每個數字選擇時能夠知道前面的選擇是選了哪些並且停在哪個index 所以有考慮到用後綴的方式建立在每個pos上 nums2每個點往後看最近的各個數值index在哪
但是後來在實現DP的時候發現很難使用 因為還是需要重頭遍歷一下前面的狀況 既然如此前面的狀況就肯定符合index條件
3. 看了一下數具規模 n = 500 兩個數組長度最多500 這題可以允許 n^2解
如此看來我會想到dp雙序列去解這題 此題是藏的很好的LCS考題
*/
