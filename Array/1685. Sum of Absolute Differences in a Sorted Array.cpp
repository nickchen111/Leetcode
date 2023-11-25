/*
1685. Sum of Absolute Differences in a Sorted Array
*/

//TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> getSumAbsoluteDifferences(vector<int>& nums) {
        int n = nums.size();
        vector<int> presum(n+1,0);
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+nums[i-1];
        }
        vector<int> res(n);
        for(int i = 0; i<n; i++){
            res[i] = (nums[i]*(i+1)-presum[i+1])+(presum[n]-presum[i+1])-(nums[i]*(n-i-1));
        }

        return res;
    }
};

/*
[x x x x i x x x x x]
         4.        9  n = 10
*/
