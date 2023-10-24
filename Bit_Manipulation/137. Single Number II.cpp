/*
137. Single Number II
*/


//TC:O(n) SC:O(1)
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        vector<int> bits(32,0);
        int n = nums.size();
        for(auto x:nums){
            for(int i = 0; i<32; i++){
                bits[i] += (x >> i)&1;
            }
        }

        int res = 0;
        for(int i = 0; i<32; i++){
            res += (bits[i]%3 << i);
        }

        return res;
    }
};

/*
此題要想到三個三個如果除以三餘數必定是0 剩下的就會是落單的數字
轉成二進位制才能做
十進位遇到本身就是三的倍數會判斷失誤

可再進一步優化空間
*/
