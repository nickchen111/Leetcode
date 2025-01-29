// TC:O(n^2 + nlgn) SC:O(n)
class Solution {
public:
    vector<int> recoverArray(vector<int>& nums) {
        ranges::sort(nums);
        int n = nums.size();
        for(int i = 1; i < n; i++) {
            int d = nums[i] - nums[0];
            if(d == 0 || d & 1) continue;
            int k = d/2;
            vector<bool> visited(n);
            visited[i] = true; // 假設他就是higher數組的
            vector<int> ans{(nums[i] + nums[0]) / 2};
            int l = 1, r = i + 1;
            while(r < n) {
                while(l < n && visited[l]) l += 1;
                while(r < n && nums[r] - nums[l] < 2 * k) r++;
                if(r == n || nums[r] - nums[l] > 2 * k) break;
                visited[r] = true;
                ans.push_back((nums[r] + nums[l]) / 2);
                r += 1, l += 1;
            }
            if(ans.size() == n/2) return ans;
        }
        return {};
    }
};
