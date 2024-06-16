/*
330. Patching Array
*/

// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    int minPatches(vector<int>& nums, int n) {
        
        LL sum = 0;
        int m = nums.size();
        int res = 0;
        int i = 0;

        while(sum < n){
            if(i == m || sum+1 < nums[i]){
                res += 1;
                sum = sum + (sum+1);
            }
            else {
                sum = sum + (LL)nums[i];
                i++;
            }
        }

        return res;
    }
};

/*
1 2 -> 3
1 2 3 -> 6以前的都可以構造出來
1 2 3 4 -> 10以前的都可以構造出來
問說需要加入多少個數字
*/
