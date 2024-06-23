/*
3194. Minimum Average of Smallest and Largest Elements
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    double minimumAverage(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int i = 0;
        int j = nums.size()-1;
        double res = INT_MAX/2;
        while(i < j){
            double cur = ((double)nums[i] + (double)nums[j]) / 2.0;
            res = min(res, cur);
            i++;
            j--;
        }
        
        return res;
    }
};

/*
移除最小與最大 然後 兩者相加除二 問最小的結果
*/
