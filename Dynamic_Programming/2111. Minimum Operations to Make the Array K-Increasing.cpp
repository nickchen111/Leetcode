/*
2111. Minimum Operations to Make the Array K-Increasing
*/

// TC:O(nlgn) SC:O(n)
class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size();
        int res = 0;
        for(int i = 0; i < k; i ++) {
            vector<int> nums;
            int count = 0;
            for(int j = i; j < n; j+=k) {
                if(nums.empty() || nums.back() <= arr[j]) {
                    nums.push_back(arr[j]);
                }
                else {
                    auto iter = upper_bound(nums.begin(), nums.end(), arr[j]);
                    *iter = arr[j];
                }
                count += 1;
            }
            res = res + (count - (int)nums.size());
        }

        return res;
    }
};

/*
[4,1,5,2,6,2], k = 3
[1,x,1,x,x,x]

5 6 5 2 5 5
*/
