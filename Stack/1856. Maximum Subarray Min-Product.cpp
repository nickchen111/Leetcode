/*
1856. Maximum Subarray Min-Product
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int maxSumMinProduct(vector<int>& nums) {
        //求各個subarra中最小的min值*subarray總和
        int n = nums.size();
        //總和用presum在 O(1)求得 subarray用stack 求next & prev smaller
        vector<LL> presum(n+1,0);
        for(int i =1; i<=n; i++){
            presum[i] = presum[i-1]+nums[i-1];
        }

        LL res = 0;
        vector<int> nextSmaller(n,n);
        vector<int> prevSmaller(n,-1);
        stack<int> s;//單調遞增
        for(int i = 0; i<n; i++){
            while(!s.empty() && nums[s.top()] > nums[i]){
                nextSmaller[s.top()] = i;
                s.pop();
            }
            if(!s.empty()) prevSmaller[i] = s.top();
            s.push(i);
        }

        for(int i = 0; i<n; i++){
            int a = prevSmaller[i], b = nextSmaller[i];
            res = max(res,(presum[b]-presum[a+1])*nums[i]);
        }

        return res%M;
    }
};

/*
x x x a x x x i x x x b

*/
