/*
1498. Number of Subsequences That Satisfy the Given Sum Condition
*/

//TC:O(n+nlgn) SC:O(n)
class Solution {
public:
    int numSubseq(vector<int>& nums, int target) {
        //此題是要求子序列 如果是說subarray的話好像也只能有O(n^2)的解 因為每個最大最小值的group需要去互相對應
        int n = nums.size();
        //既然是求子序列那麼順序不重要 排序後方便查找每個對應的數值
        sort(nums.begin(),nums.end());
        long long M = 1e9+7;
        //預處理
        vector<long long> power(n+1,1);
        for(int i = 1; i<=n; i++){
            power[i] = (power[i-1]*2)%M;
        }
        long long res = 0;
        int j = n-1;
        for(int i = 0; i<n; i++){
            while(j>=i && nums[i]+nums[j]>target){
                j--;
            }
            if(j<i) break;
            res = (res+power[j-i])%M;
        }

        return res;
    }
};

/*
ex: 
3 3 4 5 6 8 9 9 10 target = 8 
i.    j
i一定要有其他三個可有可無 也就是2^3的組合
*/
