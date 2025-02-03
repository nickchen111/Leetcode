/*
2565. Subsequence With the Minimum Score
*/

// 2025.0203 不同定義 
class Solution {
public:
    int minimumScore(string s, string t) {
        int m = s.size(), n = t.size();
        vector<int> suffix(m); // 儲存能夠匹配的t長度
        int i = m-1, j = n-1;
        while(i >= 0 && j >= 0) {
            if(s[i] == t[j]) j -= 1;
            suffix[i] = n - 1 - j;
            i -= 1;
        }
        int prefix = 0, ans = n - suffix[0];
        i = 0, j = 0;
        while(i < m && j < n) {
            if(s[i] == t[j]) j += 1;
            prefix = j;
            ans = min(ans, max(0, n - prefix - (i + 1 < m ? suffix[i+1] : 0)));
            i += 1;
        }
        return ans;
    }
};


// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumScore(string s, string t) {
        int n = s.size();
        int m = t.size();
        
        vector<int> suffix(n+1);
        suffix[n] = m;
        int j = m-1;
        for (int i = n - 1, j = m - 1; i >= 0; i--) {
            if (j >= 0 && s[i] == t[j]) {
                j--;
            }
            if(j < 0) return 0; // t 為 s 的子序列
            suffix[i] = j + 1; // 後綴可以計入的起點下標位置
        }

        int res = suffix[0];

        for(int i = 0, j = 0; i < n; i++){
            if(j < m && s[i] == t[j]){
                j++;
            }

            res = min(res, suffix[i+1] - j);
        }

        return res;

    }
};
