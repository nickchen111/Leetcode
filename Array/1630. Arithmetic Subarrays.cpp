/*
1630. Arithmetic Subarrays
*/

//TC:O(m*nlgn) SC:O(n) m為query次數
class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        int n = l.size();
        vector<bool> res(n);
        for(int i = 0; i<n; i++){
            int left = l[i]; int right = r[i];
            vector<int> arr({nums.begin()+left,nums.begin()+right+1});
            sort(arr.begin(),arr.end());
            bool flag = true;
            for(int j = 2; j<arr.size(); j++){
                if(j-2 >= 0 && arr[j]-arr[j-1] != arr[j-1]-arr[j-2]){
                    flag = false;
                    res[i] = false;
                    break;
                }
            }
            if(flag)
                res[i] = true;
        }

        return res;
    }
};
