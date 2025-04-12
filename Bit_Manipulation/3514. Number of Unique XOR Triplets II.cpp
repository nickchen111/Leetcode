// TC:O(n^2) SC:O(n^2) 
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> st;
        st.insert(0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                st.insert(nums[i] ^ nums[j]);
            }
        }
        unordered_set<int> set;
        for (int k = 0; k < n; k++) {
            for (auto &pairXor : st) {
                set.insert(pairXor ^ nums[k]);
            }
        }
        
        return set.size();
    }
};
