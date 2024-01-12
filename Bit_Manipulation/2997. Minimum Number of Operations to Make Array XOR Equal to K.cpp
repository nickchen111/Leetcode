/*
2997. Minimum Number of Operations to Make Array XOR Equal to K
*/

// TC:O(32*n) SC:O(32)
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        vector<int> bit(32,0);//只care 1
        int n = nums.size();
            
        for(int i = 0; i < n; i++){
            int cur = nums[i];
            for(int j = 0; j < 32; j++){
                int x = ((cur >> j) & 1);
                if(x == 1) bit[j] = (bit[j] + 1) % 2;
            }
        }
        
        int res = 0;
        for(int i = 0; i < 32; i++){
            int x = ((k >> i) & 1);
            int y = bit[i];
            if(x != y) res += 1;
        }
        
        return res;
    }
};

/*
可以翻轉任意數字的元素二進位表示的01 問最少翻幾次能讓整個元素XOR = k
XOR
相同為零不同為一
2 1 3 4 
-> 0 1 0, 0 0 1, 0 1 1, 1 0 0 -> 0 1 1 , 0 1 1, 1 0 0  -> 0 0 1 , 1 0 0 -> 1 0 0 
0 1 1 -> 0 1 0
0 1 0 -> 1 1 0
具有交換律 可以看現在每個位數上有幾個 1 & 0 來判斷還差幾項 ->幾個1 or 0 可以
偶數時全部轉成 0 
奇數時 就會是1 目前某位上有 3個 0 兩個 1那會是 0 0 0 -> 0 , 兩個 0 , 3 個 1 -> 0 0 1
所以奇數個零 結果會是 0 奇數個1結果會是1 偶數1就會是0 0不管有幾個都會自己變成0
k = 0 0 1
*/
