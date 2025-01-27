/*
2401. Longest Nice Subarray
*/

// 2025.01.27
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();
        int ans = 1, i = 0, state = 0;
        for(int j = 0; j < n; j++) {
            while(state & nums[j]) {
                state ^= nums[i++];
            }
            state |= nums[j];
            ans = max(ans, j - i + 1);
        }
        return ans;
    }
};

// TC:O(n) SC:O(1)
class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();
        int j = 0;
        int count = 0;
        int res = 0;
        for(int i = 0; i<n; i++){
            while(j < n && (count & nums[j]) == 0){
                count+=nums[j];
                res = max(res,j-i+1);
                j++;
            }
            count-=nums[i];
        }
        return res;
    }
};

/*
意即希望對於區間內的每個bit位上都只出現一個1
此題跟第三題很像 但是此題其實並不需要開一個數組去紀錄32個bit位數量 因為只要某個位置數量超過的話
那就不會加入他 反而要減掉他 所以直接用int 做相加減代表bit位上的狀況即可
*/
