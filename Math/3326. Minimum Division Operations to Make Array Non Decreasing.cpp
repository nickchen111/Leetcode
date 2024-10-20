/*
3326. Minimum Division Operations to Make Array Non Decreasing
*/

// TC:O(nlgU) SC:O(n)
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        int minVal = INT_MAX;
        unordered_map<int,int> map; //某數字除了本身與1對應最大divisor
        for(int i = n-1; i >= 0; i--) {
            // 16 -> 2*2*2*2
            while(nums[i] > minVal) {
                if(map.find(nums[i]) != map.end()) {
                    nums[i] /= map[nums[i]];
                    res += 1;
                }
                else {
                    int cur = nums[i];
                    bool flag = 0;
                    for(int j = 2; j*j <= nums[i]; j++) {
                        if(cur % j == 0) {
                            int tmp = max(j, cur/j);
                            map[nums[i]] = tmp;
                            flag = 1;
                            break;
                        }
                    }
                    
                    if(flag == 0) return -1;
                    nums[i] /= map[nums[i]];
                    res += 1;
                }
                
            }
            minVal = min(minVal, nums[i]);
        }
        
        return res;
    }
};

/*
用最少次數讓數組變成單調遞增
每個數字可以用比他小的公因數除
首先從後面開始如果他後面有比他小的數字就處理 如果是質數就gg 不是的話 想一下該如何做
*/
