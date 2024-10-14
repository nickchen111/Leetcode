/*
2530. Maximal Score After Applying K Operations
*/

// TC:O(klgn + n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maxKelements(vector<int>& nums, int k) {
        int n = nums.size();
        priority_queue<int, vector<int>, less<>> pq;
        for(auto &x : nums) {
            pq.push(x);
        }

        LL res = 0;
        while(k--) {
            res += pq.top();
            int cur = pq.top();
            pq.pop();
            cur = cur % 3 ? (cur/3 + 1) : cur/3;
            pq.push(cur);
        }

        return res;
    }
};
