/*
2741. Special Permutations
*/

// TC:O(n*2^n) SC:O(14*2^14)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
    vector<int> nums;
    int n;
    LL memo[14][1<<14]; // 這次選了第幾個 然後目前已經選了哪些
public:
    int specialPerm(vector<int>& nums) {
        this->nums = nums;
        this->n = nums.size();
        for(int i = 0; i<n; i++){
            for(int state = 0; state < (1<<n); state++){
                memo[i][state] = -1;
            }
        }

        LL res = 0;
        for(int i = 0; i<n; i++){
            res += DFS(0,i, 1<<i); // 目前選了i當作我的第0 個idx 上的數字 並且選擇的總情況是state
            res %= M;
        }

        return res;
    }
    LL DFS(int i, int p, int state){
        if(i == n-1) return 1;//選完了並且只有這一種可能

        if(memo[p][state] != -1) return memo[p][state];

        LL count = 0;
        for(int q = 0; q<n; q++){
            if((state>>q)&1) continue;//代表之前已經選過了
            if(nums[p]%nums[q] != 0 && nums[q]%nums[p] != 0) continue;
            count += DFS(i+1, q, state+(1<<q));
            count %= M;
        }

        memo[p][state] = count;

        return count;
    }
};

/*
此題問說我的數字可以怎麼排序讓每個nums[i]%nums[i+1] == 0 or nums[i+1]%nums[i] == 0 ->看數據規模可以得知要用排列組合每個都試試 並且善用剪枝技巧記憶化
DFS(i,p,state) -> DFS(i+1, q, state2) : 選了幾項 這次選的符合條件的數字為 之後還有幾項可以選
number of special permutations when we set ith number as p and we have selectede number from state
*/
