// TC:O(n^2) SC:O(n^2) 
class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        vector<int> arr(nums.begin(), unique(nums.begin(), nums.end()));
        int n = arr.size();
        unordered_set<int> st;
        st.insert(0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                st.insert(arr[i] ^arr[j]);
            }
        }
        unordered_set<int> set;
        for (int k = 0; k < n; k++) {
            for (auto &pairXor : st) {
                set.insert(pairXor ^ arr[k]);
            }
        }
        
        return set.size();
    }
};
