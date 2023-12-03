/*
1218. Longest Arithmetic Subsequence of Given Difference
*/


// 第一種做法 TC:O(n) SC:O(n)
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int diff) {

        int n = arr.size();
        vector<int> dp(n,1);
        unordered_map<int, int> map;

        int res = 0;
        
        for(int i = n-1; i >= 0; i--){
           if(map.find(arr[i]+diff) != map.end()){
               int idx = map[arr[i]+diff];
               dp[i] = (dp[idx]+1);
           }
           map[arr[i]] = i;
           res = max(res, dp[i]);
        }
        
        return res;
    }
};

//第二種 
class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        // 另種想法 將map存放的是以某個數做結尾時 能有的最長長度動態更新
        unordered_map<int,int> map;
        int res = 0;
        for(auto x:arr){
            if(map.find(x - difference) != map.end()){
                map[x] = map[x - difference] +1;
            }
            else map[x] = 1;

            res = max(res, map[x]);
        }

        return res;
    }
};

/*
此題給你一公差 要求滿足此公差的最長subsequence為多長
1.我的想法是從後往前遍歷 dp[i]代表以i作為開頭的最長序列多長 過程中動態更新map存的key: val value: idx 這樣每次選的都會是越靠前的idx 越有利於後面選數字
2. 另種想法 將map存放的是以某個數做結尾時 能有的最長長度動態更新 這種做法就可以由前往後遍歷
*/
