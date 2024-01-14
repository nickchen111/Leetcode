/*
823. Binary Trees With Factors
*/

// 1/14
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        int n = arr.size();
        vector<LL> dp(n,1);
        sort(arr.begin(), arr.end());
        unordered_map<int,int> map;
        for(int i = 0; i < n; i++){
            map[arr[i]] = i;
        }
        LL res = 1;
        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++){
                if(arr[i] % arr[j] == 0 && map.find(arr[i]/arr[j]) != map.end()){
                    dp[i] = dp[i]%M + (dp[j]*dp[map[arr[i]/arr[j]]])%M;
                }
            }
            res = (res + dp[i]) % M;
        }

        return res;

    }
};

/*
構造樹 每顆非子樹的節點的數值都是他的子樹的乘積 並且他的數字可以重複使用
vector<int> dp(n,1);
// ex : 2 3 4 6 12 
     12
    /  \
    3   4 
       /  \ 
      2    2
for(int i = 1; i < n; i++){
    for(int j = 0; j < i; j++){
        if(nums[i] % nums[j] == 0 && map.find(nums[i]/nums[j])){
            dp[i] = dp[i] + (dp[j]*dp[map[nums[i]/nums[j]]]);
        }
    }
}
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        // DP 題
        //先sort才能從小問題建構出大問題
        sort(arr.begin(), arr.end());
        long long M = 1e9+7;
        unordered_map<int, long> dp;
        for(int i = 0; i<arr.size(); i++){
            dp[arr[i]] = 1;//每個數自己會是一個tree
            for(int j = 0; j<i; j++){
                if(arr[i]%arr[j]==0 && dp.count(arr[i]/arr[j])){
                    dp[arr[i]] += (dp[arr[j]]*dp[arr[i]/arr[j]])%M;
                }
            }
        }

        long res = 0;
        for(auto map:dp){
            res+=map.second;
        }

        return res%M;
    }
};
