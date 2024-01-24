/*
3012. Minimize Length of Array Using Operations
*/

// TC:O(n+nlgn) SC:O(1)
class Solution {
public:
    int minimumArrayLength(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int minVal = nums[0];
        int count = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] == minVal) count++;
            else if(nums[i] % minVal != 0) return 1;
        }

        int res;
        if(count % 2 == 0) res = count/2;
        else res = count/2+1;
        
        return res;
    }
};

/*
選擇的兩個數字會消失並且他們要是大於0 他們的餘數會加入數組 想要最少化數組長度
首先會想到不會讓兩個相同數字香消 因為會製造無法消除的0 
再來就是這題的第一個策略了 如果有唯一的一個最小值 他就可以將所有的數字消掉 只保留他 但如果出現重複次數的最小值 就必須要去找是不是有人可以跟他相除不為0
如果有的話就還是return 1 沒有的話就代表最後會剩下重複的這麼多最小值 偶數的話就是count/2 奇數就是count/2+1 個ex:2,0,0
*/
