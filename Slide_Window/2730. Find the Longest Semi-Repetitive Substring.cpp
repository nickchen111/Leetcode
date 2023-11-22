/*
2730. Find the Longest Semi-Repetitive Substring
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) {
        //此題也算是限制條件讓你去找最長長度那類的滑窗
        int count = 0;
        int j =0;
        int n=s.size();
        int res = 0;
        char tail;
        
        for(int i = 0; i<n; i++){
            while(j <n && count < 2){
                tail = s[j];
                j++;
                if(tail == s[j]) count++;
            }
            res = max(res,j-i);
            if(i+1 < n && s[i] == s[i+1]) count--;
        }

        return res;
    }
};
