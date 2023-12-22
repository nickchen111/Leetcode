/*
1422. Maximum Score After Splitting a String
*/

// Two Pass TC:O(n) SC:O(n)
class Solution {
public:
    int maxScore(string s) {
        int count1 = 0;
        int n = s.size();
        vector<int> one(n);
        //不包含自己
        for(int i = n-1; i >= 0; i--){
            one[i] = count1;
            if(s[i] == '1') count1 += 1;
        }

        int res = 0;
        int count0 = 0;
        for(int i = 0; i < n-1; i++){
            if(s[i] == '0') count0 += 1;
            res = max(res, count0 + one[i]);

        }

        return res;
    }
};

/*
分割字串 左邊0的個數 加上1的個數相加為分數 求最大值
*/
