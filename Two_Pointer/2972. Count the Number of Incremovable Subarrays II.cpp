/*
2972. Count the Number of Incremovable Subarrays II
*/

// TC: Two Pointer O(n) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), INT_MIN);
        nums.push_back(INT_MAX);

        int L = 1;
        while(L <= n){
            if(nums[L] < nums[L+1]) L+=1;
            else break;
        }
        int R = n;
        while(R >= 1){
            if(nums[R] > nums[R-1]) R--;
            else break;
        }

        if(R < L) return n*(n-1)/2 + n; // 整段都遞增
        LL res = 0;
        int j = R;
        for(int i = 0; i <= L; i++){
            while(j <= n+1 && nums[i] >= nums[j]){
                j++;
            }
            // x x x n
            res += (n+2-j);
        }

        return res;

    }
};


// Binary Search TC:O(n+ m*lgk) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long incremovableSubarrayCount(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), INT_MIN);
        nums.push_back(INT_MAX);
        //真正數字範圍從1~n
        int L = 1;
        while(L <= n){
            if(nums[L] < nums[L+1]) L++;
            else break;
        }

        int R = n;
        while(R >= 1){
            if(nums[R] > nums[R-1]) R--;
            else break;
        }

        if(R < L) return n*(n-1)/2 + n;

        LL res = 0;
        for(int i = 0; i <= L; i++){
            auto iter = upper_bound(nums.begin()+R, nums.end(), nums[i]);
            res += (nums.end() - iter);
        }

        return res;
    }
};

/*
此題想問你可以刪除多少種subarray讓剩下的元素合併起來為遞增序列
重點在於接起來要遞增 那麼前後兩段接起來的自己也要是遞增
Thinking: 左邊找一段連續遞增區間 右邊找一段連續遞增區間 對左邊選一個斷點 然後找右邊區間他可以接在哪 二分
但有個問題 可能沒有左段 or 右段 or中段
1. case1 中段非遞增區間為空集: 沒有,  選取任意區間 n個區間 選兩個頭尾 n*(n-1) / 2; 因為頭尾會重複到一樣的 + n 因為 自己一個點也可以是一個區間
2. case 2 L/R 4種可能 最好的解法是 在nums數組前面置入一個最小值 後面置入最大值 當作可能都不取的狀態 也有可能是兩邊都沒東西的狀態 然後一樣從Ｌ二分過去
用INT_MIN找到INT_MAX代表全刪 這題來說也是可以的
*/
