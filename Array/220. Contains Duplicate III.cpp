/*
220. Contains Duplicate III
*/

// TC:O(nlgnlgn) SC:O(n)
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        multiset<long> set;
        for(int j = 0; j<n; j++){
            //用set.lower_bound 就可以找到第一個重複元素存在的位址 然後只刪除他！
            if(j > k) set.erase(set.lower_bound(nums[j-k-1]));
            auto pos = set.lower_bound((long)(nums[j]-t));
            if(pos != set.end() && *pos-nums[j] <= t) return true;
            set.insert(nums[j]);
        }
        return false;
    }
};

/*
此題限制
1.位置差限制->窗口
2.value差限制
想法會是固定一個i 看能否高效找到j  o(n)*lgn  or 1
-t <= nums[i]-nums[j] <=t
nums[j]-t <= nums[i] <= nums[j]+t
二分去找此窗口
*/
