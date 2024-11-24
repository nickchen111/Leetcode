/*
3362. Zero Array Transformation III
*/

// TC:O(n+ mlgm) SC:O(m + n)
class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        sort(queries.begin(), queries.end());
        int m = queries.size();
        int n = nums.size();
        int idx = 0;
        int sum = 0;
        vector<int> diff(n+1);
        priority_queue<int, vector<int>, less<>> pq;// 彈出最長的終點 但是暫時沒用到 反悔貪心
        for(int i = 0; i < n; i++) {
            sum += diff[i];
            while(idx < m && queries[idx][0] <= i) {
                pq.push(queries[idx][1]);
                idx++;
            }
            while(sum < nums[i] && !pq.empty() && pq.top() >= i) {
                diff[pq.top()+1] -= 1;
                pq.pop();
                sum += 1;
            }

            if(sum < nums[i]) return -1;
        }

        return (int)pq.size();
        
    }
};
