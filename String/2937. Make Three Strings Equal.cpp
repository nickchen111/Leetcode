/*
2937. Make Three Strings Equal
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3) {
        //前一個字一定要一樣
        int m = s1.size(); int n = s2.size(); int t = s3.size();
        if(s1[0] != s2[0] || s1[0] != s3[0]) return -1;
        
        //開始比較後面的字
        int minNum = min(m,min(n,t));
        int idx = minNum;
        for(int i =0; i<minNum; i++){
            if(s1[i] != s2[i] || s1[i] != s3[i]){
                idx = i;
                break;
            }
        }
        
        
        int res = 0;
        res+=(m-idx);
        res+=(n-idx);
        res+=(t-idx);
       
        return res;
    }
};
