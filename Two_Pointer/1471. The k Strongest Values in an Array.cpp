// TC:O(nlgn) SC:O(1)
class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        ranges::sort(arr);
        int n = arr.size(), i = 0, j = n - 1;
        int median = arr[(n-1)/2];
        vector<int> ans;
        while(ans.size() < k) {
            if(abs(arr[i] - median) <= abs(arr[j] - median)) {
                ans.push_back(arr[j--]);
            }
            else {
                ans.push_back(arr[i++]);
            }
        }
        return ans;
    }
};
