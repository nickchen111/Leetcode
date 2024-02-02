/*
1291. Sequential Digits
*/


// Enumeration 列舉 TC:O(n^3) SC:O(n) n = 9
class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        vector<int> arr({1,2,3,4,5,6,7,8,9});
        vector<int> res;
        //最小長度到最大長度
        int minLen = 0;
        int maxLen = 0;
        int curNum = low;
        while(curNum != 0){
            minLen += 1;
            curNum /= 10;
        }
        curNum = high;
        while(curNum != 0){
            maxLen += 1;
            curNum /= 10;
        }

        
        for(int len = minLen; len <= maxLen; len++){
            for(int i = 0; i + len - 1 < arr.size(); i++){
                int cur = 0;
                for(int j = i; j < i+len; j++){
                    cur = cur*10 + arr[j];
                }
                if(cur >= low && cur <= high) res.push_back(cur);
                else if(cur > high) break;
            }
        }

        return res;
    }
};

// Backtrack TC:O(n^n) SC:O(n) n = 9
class Solution {
    unordered_set<int> set2;
    unordered_set<int> set;
public:
    vector<int> sequentialDigits(int low, int high) {
        helper(high,1, 0, 0);
        helper2(low-1,1, 0, 0);
        
        vector<int> ret;
        for(auto s : set2){
            if(set.find(s) == set.end()) ret.push_back(s);
        }
        

        sort(ret.begin(), ret.end());

        return ret;
    }
    void helper(int high, int cur, int sum, bool flag){
        if(sum <= high) set2.insert(sum);
        if(sum*10 > high) return;
        if(sum > high) return;

        if(cur + 1 <= 10) {
            int newSum = sum*10 + cur;
            helper(high, cur+1, newSum, 1);
            if(flag == 0) helper(high, cur+1, sum, 0);
        }
    }
    void helper2(int high, int cur, int sum, bool flag){
        if(sum <= high) set.insert(sum);
        if(sum*10 > high) return;
        if(sum > high) return;

        if(cur + 1 <= 10) {
            int newSum = sum*10 + cur;
            helper2(high, cur+1, newSum, 1);
            if(flag == 0) helper2(high, cur+1, sum, 0);
        }
    }
};
