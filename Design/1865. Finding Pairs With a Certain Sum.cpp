// TC:O(n) SC:O(n)
class FindSumPairs {
    unordered_map<int,int> mp;
    vector<int> nums1, nums2;
public:
    FindSumPairs(vector<int>& nums1, vector<int>& nums2) {
        this -> nums1 = nums1;
        this -> nums2 = nums2;
        for (auto & num : nums2) {
            mp[num] += 1;
        }
    }
    
    void add(int index, int val) {
        mp[nums2[index]] -= 1;
        nums2[index] += val;
        mp[nums2[index]] += 1;
    }
    
    int count(int tot) {
        int ans = 0;
        for (auto & num : nums1) {
            ans += mp[tot - num];
        }
        return ans;
    }
};
