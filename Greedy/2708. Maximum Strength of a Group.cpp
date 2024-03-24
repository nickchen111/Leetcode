/*
2708. Maximum Strength of a Group
*/

// 3/24 Greedy 
class Solution {
    using LL = long long;
public:
    long long maxStrength(vector<int>& nums) {
        int n = nums.size();
        LL res = 1;
        LL maxVal = *max_element(nums.begin(), nums.end());
        
        vector<int> neg;
        bool flag = 0;
        for(auto x : nums){
            if(x > 0) {
                res*=x;
                flag = 1;
            }
            else if(x < 0) neg.push_back(x);
        }
        sort(neg.begin(), neg.end());

        int m = neg.size();
        
        if(m % 2 == 0){
            for(auto x : neg){
                res*=x;
                flag = 1;
            }
        }
        else {
            m -= 1;
            for(int i = 0; i < m; i++){
                res *= neg[i];
                flag = 1;
            }
        }

        if(flag) return res;
        else return maxVal;
       
    }
};

// Greedy TC:O(n) SC:O(n)
class Solution {
public:
    long long maxStrength(vector<int>& nums) {
        long long res = 1;
        int n = nums.size();
        if(n == 1) return nums[0];

        multiset<int> set;
        bool flag1 = 1;
        bool flag2 = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] > 0){
                res *= nums[i];
            }
            else if(nums[i] < 0){
                set.insert(nums[i]);
            }
            else flag2 = 1;///代表有0
            if(nums[i] > 0) flag1 = 0;//代表有比0大的數字
            
        }

        if(flag1 && flag2 && set.size() == 1) return 0; // 0 -7 
        else if(set.size() == 0 && flag2 && flag1) return 0; // 0000000

        if(set.size() % 2 == 0){
            for(auto p:set){
                res *= p;
            }
            return res;
        }
        else {
            set.erase(--set.end());
            for(auto p:set){
                res *= p;
            }
            return res;
        }
    }
};

// Backtrack TC:O(2^n) SC:O(2^n)
class Solution {
    long long res = INT_MIN;
public:
    long long maxStrength(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];

        backtrack(nums,0,1,0);
        
        return res;
    }
    void backtrack(vector<int>& nums, int idx, long long product, int count){
        if(nums.size() == idx){
            if(count != 0) res = max(res, product);
            return;
        }

        backtrack(nums, idx + 1, product*nums[idx], count+1); // pick
        backtrack(nums, idx + 1 , product, count); //not pick

    }
};

/*
此題想用一串正負數都有的數組 挑元素相乘讓數值最大
Greedy: 此想法就是如果有正數就給他乘 如果有負數就取偶數個 但是我WA了五次才AC 因為會有很多特殊情況 ex: [0, -7] 只有一個負數 如果res 設為 1 答案錯需特判
ex: [0 0 0 0. 0 0] 都是0 也要特判有無正數以及負數
Bakctrack: 暴力解 就是取或者不取 回傳其中最大可能性
DP: 類似152題的概念 可以線性簡短code 但沒深入研究
*/
