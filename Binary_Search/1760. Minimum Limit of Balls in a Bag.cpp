/*
1760. Minimum Limit of Balls in a Bag
*/

// TC:O(n*lgM) SC:O(1)
class Solution {
public:
    int minimumSize(vector<int>& nums, int maxOperations) {
        int n = nums.size();
        int left = 1, right = *max_element(nums.begin(), nums.end());
        auto check = [&](int mid) -> bool {
            int chance = 0;
            for(int i = 0; i < n; i++) {
                if(nums[i] > mid) {
                    chance += (nums[i]/mid + (nums[i] % mid == 0 ? 0 : 1)) - 1;
                }
                if(chance > maxOperations) return false;
            }
            return true;
        };
        while(left < right) {
            int mid = left + (right - left)/2;
            if(check(mid)) {
                right = mid;
            }
            else left = mid + 1;
        }

        return left;
    }
};

/*
操作次數到1e9 所以不可能是線性解 要往lgn 或者數學解去想
然後一定是想先處理nums中大的數字
minimize maximum number -> 二分
9 -> 5,4 -> 3,2,2,2
9 要除多少次會變成3 9/2, 9/2/2 兩次 大概是 9 >> x <= 3
1001 -> 10 9/2^x <= 3
2^x * 3 >= 9 -> 2^x >= 3 -> x = 2
2^x *3 >= 10 -> 2^x >= 13/3 向上取整 = 5 x = 3
13 -> 6,7 -> 3,3,4,3 13/3 + (13%3 == 0 ? 0 : 1)
*/
