/*
2962. Count Subarrays Where Max Element Appears at Least K Times
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) {
        long long res = 0;
        int n = nums.size();
        int num = 0;
        unordered_map<int, vector<int>> map;
        for(int i = 0; i < n; i++){
            map[nums[i]].push_back(i);
            if(nums[i] > num){
                num = nums[i];
            }
        }
        
        //開此計算最大的數字出現的可能性
        //這裡也不需擔心他出現的次數小於k 如果小於就完全不會進入loop
        int m = map[num].size();

        for(int j = 0; j < m; j++){
            if(j + k -1 < m){
                long long a = map[num][j] - ( j == 0 ? -1 : map[num][j-1] );
                long long b = n - map[num][j+k-1];
                res += (a*b);
            }
        }
        
        return res;
    }
};

/*
此題要求最大的那個數字頻率大於等於k的狀況下有的subarray總數
1. 先用map計算每個出現的數字對應的位置 以及最大數字是哪個
2. 藉由idx 計算可能組成的subarray 數量 ex: 出現頻率 k =2 
x x x 3 x x x 3 x x x 3 x x 
a  = pos[i] - pos[i-1] , b = n - pos[i+k-1] res += (a*b) count subarray的套路操作
0 1 2 3 4 5 6 7 8 9 1011  13  n = 14
*/
