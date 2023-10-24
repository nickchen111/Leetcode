/*
368. Largest Divisible Subset
*/

//tc: O(n^2) sc:O(n)
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return nums;
        sort(nums.begin(), nums.end());
         //此題用兩個數組去紀錄 一個紀錄長度 一個紀錄index 之間的前後關係貌似會比較好理解

        vector<int> dp(n,1);
        vector<int> prev(n,-1);
        
        for(int i = 0; i<n; i++){
            for(int j = 0; j<i; j++){
                if(nums[i] % nums[j] == 0){
                    dp[i] = max(dp[i], dp[j]+1);
                    if(dp[i] == dp[j]+1){
                        prev[i] = j;//  紀錄此index上一個index在哪
                    }
                }
            }
        }

        vector<int> res;
        int len = 0;
        int index = 0;
        //找到最長的長度與其index
        for(int i = 0; i<n;i++){
            while(dp[i] > len){
                len = dp[i];
                index = i;
            }   
        }
        
        while(index != -1){
            res.push_back(nums[index]);
            index = prev[index];
        }

        return res;

    }
};


/*
dp[i] nums[0:i]總共有幾個數字可以互相為子集 largest subset answer
此題用兩個數組去紀錄 一個紀錄長度 一個紀錄index 之間的前後關係貌似會比較好理解 
*/
