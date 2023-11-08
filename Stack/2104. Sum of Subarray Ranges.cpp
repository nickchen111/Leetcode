/*
2104. Sum of Subarray Ranges
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL res;
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = nums.size();
        vector<int> prevSmaller(n,-1);
        vector<int> nextSmaller(n,n);
        vector<int> prevLarger(n,-1);
        vector<int> nextLarger(n,n);
        stack<int> s;//先求最小再求最大
        for(int i = 0; i<n; i++){
            while(!s.empty() && nums[s.top()] > nums[i]){
                nextSmaller[s.top()] = i;
                s.pop();
            }
            if(!s.empty()) prevSmaller[i] = s.top();
            s.push(i);
        }

        while(!s.empty()){
            s.pop();
        }

        for(int i = 0; i<n; i++){
            while(!s.empty() && nums[s.top()] < nums[i]){
                nextLarger[s.top()] = i;
                s.pop();
            }
            if(!s.empty()) prevLarger[i] = s.top();
            s.push(i);
        }
        LL maxSum = 0; LL minSum = 0;
        for(int i =0; i<n; i++){
            int l = prevLarger[i]; int r = nextLarger[i];
            int a = prevSmaller[i]; int b = nextSmaller[i];
            maxSum+=(LL)nums[i]*(i-l)*(r-i);
            minSum+=(LL)nums[i]*(i-a)*(b-i);
        }

        return maxSum-minSum;
    }
};

/*
之前的題目求最小的我會 一個區間最小的很好找 那還要找最大呢
->sum of all subarray maximum - sum of all subarray mininmum
*/
