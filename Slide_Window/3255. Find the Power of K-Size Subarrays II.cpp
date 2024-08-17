/*
3255. Find the Power of K-Size Subarrays II
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> resultsArray(vector<int>& nums, int k) {
        int n = nums.size();
        
        vector<int> res;
        deque<int> dq;
        for(int i = 0; i < n; i++){
            if(i < k-1){
                while(!dq.empty() && nums[dq.back()]+1 != nums[i]){
                    dq.pop_front();
                }
                dq.push_back(i);
            }
            else {
                while(!dq.empty() && nums[dq.back()]+1 != nums[i]){
                    dq.pop_front();
                }
                dq.push_back(i);
                while(dq.size() > k){
                    dq.pop_front();
                }
                
                if(dq.size() == k) res.push_back(nums[dq.back()]);
                else res.push_back(-1);
            }
        }
        
        return res;
        
    }
};

/*
必須要是嚴格單調遞增 並且k個一組 他們的最大元素為何?
*/
