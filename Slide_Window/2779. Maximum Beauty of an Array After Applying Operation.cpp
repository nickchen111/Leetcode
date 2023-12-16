/*
2779. Maximum Beauty of an Array After Applying Operation
*/

// TC:O(nlgn + n) SC:O(1)
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int j = 1;
        int n = nums.size();
        int res = 1;
        int minVal = nums[0];
        for(int i = 0; i < n; i++){
            minVal = nums[i];
            while(j < n && nums[j] - minVal <= 2*k){
                res = max(res, j-i+1);
                j++;
            }
        }

        return res;

    }
};

// Binary Search  TC:O(5*nlgn + n) SC:O(1)
class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int res = 0;
        for(int i = 0; i < n; i++){
            //把自己當作最大值 有無剛好等於自己-2*k的
            int x = upper_bound(nums.begin(), nums.end(), nums[i]) - lower_bound(nums.begin(), nums.end(), nums[i]-2*k);
            int y = upper_bound(nums.begin(), nums.end(), nums[i]+k) - lower_bound(nums.begin(), nums.end(), nums[i]-k);
            res = max(res, max(x,y));
        }

        return res;

    }
};

/*
此題又是個可以對數組做無限次操作的題目 問說每個index可以變成+-k他的數字 那麼最長subsuquence可以組成多長
1 2 4 6 8 10 12 12 12 k = 2
每個數字當下都會回頭看能否相減後涵蓋之前的數字 如果可以就減 並且更改自己 不行就維持原本數字往後走
1 3 5 6 10 15 22 28 39 54 k = 10
就有點像最小跟最大的數字不能超過2*k即可 因為最小數字可以加k 最大數字能夠減k
*/
