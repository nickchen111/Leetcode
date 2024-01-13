/*
805. Split Array With Same Average
*/


//背包 + bit 狀態壓縮 最優解  TC:O(n*total) SC:O(n*total)
class Solution {
    int dp[300005];
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if(total == 0){
            if(nums.size() == 1) return false;
            else return true;
        }
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        dp[0] = 1;// bit上代表 0
        int curSum = 0;
        for(int i = 0; i < nums.size(); i++){
            curSum += nums[i];
            for(int sum = curSum; sum >= nums[i]; sum--){
                dp[sum] |= (dp[sum-nums[i]]<<1); // 因為原先可能就有些組合可以組成sum不該變動
                if(sum * n % total == 0){
                    int num = sum * n / total;
                    if(num != 0 && num != n && (dp[sum]>>num) & 1) return true;
                }
                
            }
        }

        return false;
    }
};

// 背包次優解 TC:O(n*total*num) SC:O(n*total*num)
class Solution {
    bool dp[300005][31];
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        dp[0][0] = 1;
        int curSum = 0;
        for(int i = 0; i < nums.size(); i++){
            curSum += nums[i];
            for(int sum = curSum; sum >= nums[i]; sum--){
                // num 不需取到n-1個 一半就可以了 因為分兩組 肯定有一組元素少於n/2 考慮找元素較少的那組
                for(int num = n/2+1; num >= 1; num--){
                    if(dp[sum-nums[i]][num-1] == 1){
                        dp[sum][num] = 1;
                        if(num != n && total*num == n*sum) return true; // num != n 防範 n == 2的狀況
                    }
                }
            }
        }

        return false;
    }
};


//背包優化前 多開了個數組 -> TLE 
class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        vector<vector<bool>> dp(total+1, vector<bool>(n+1));
        dp[0][0] = 1;
        for(int i = 0; i < nums.size(); i++){
            auto dp_tmp = dp; // 這裡還有深度拷貝過程會花時間 需要倒著來
            // sum 從 nums[i] 開始更快 不用考慮相剪負數狀況
            for(int sum = total; sum >= nums[i]; sum--){
                // num 不能取到n
                for(int num = 1; num < n; num++){
                    if(dp_tmp[sum-nums[i]][num-1] == 1){
                        dp[sum][num] = 1;
                        if(total*num == n*sum) return true;
                    }
                }
            }
        }

        return false;
    }
};


// 優化版 Backtrack TC:O(2^n) SC:O(n)
class Solution {
    int n;
    int total;
public:
    bool splitArraySameAverage(vector<int>& nums) {
        n = nums.size();
        total = accumulate(nums.begin(), nums.end(), 0);
        sort(nums.begin(), nums.end());

        for(int num = 1; num < nums.size(); num++){
            if(total*num%n != 0) continue;
            int sum = total*num/n;
            if(DFS(num,sum,nums,0)) return true;
        }   

        return false;
    }
    bool DFS(int num, int sum, vector<int>& nums, int idx){
        if(num == 0 && sum == 0) return true;
        if(num == 0 || sum == 0 && idx != 0) return false;
        if(idx == n) return false;

        if(DFS(num-1, sum-nums[idx], nums, idx+1)) return true;
        int i = idx;
        while(i < n && nums[i] == nums[idx]) i++;
        
        if(DFS(num,sum,nums,i)) return true;

        return false;
    }
};


/*
1. Backtrack解法:
total / n = curSum / curNum 就可以忽略double平均的浮點數判斷
total*curNum = n * curSum 用這個式子去backtrack才可以過 如果無腦暴力搜索就算有剪枝還是會TLE
2. 背包 二維 紀錄dp[total][num] 用num個數字是否能拼湊出 total 還要搭配先sort過 才能剪枝
3. 背包 一維就可以知道和是sum bit : dp[sum] = 0100010 能用幾個數組成sum  能用 1 or 5個數組成sum 這題剛好30位夠用
*/
