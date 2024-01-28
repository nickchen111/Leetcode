/*
3020. Find the Maximum Number of Elements in Subset
*/

// TC:O(30*n) SC:O(n)
class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<int,int> map;
        for(auto x : nums){
            map[x] += 1;
        }
        
        int res = 1;
        for(auto p : map){
            if(p.second >= 2 && p.first == 1){
                int count = p.second;
                if(p.second % 2 == 0) res = max(res, count-1);
                else res = max(res, count);
            }
            else if(p.second >= 2){
                int val = p.first;
                int count = 2;
                bool flag = 0;
                for(int i = 2; i <= 30; i*=2){
                    long cur = pow(val,i);
                    if(cur > 1e9) {
                        break;
                    }
                    else if(map.find(cur) != map.end()){
                        if(map[cur] >= 2) count += 2;
                        else {
                            count += 1;
                            flag = 1;
                            break;
                        }
                    }
                    else {
                        count -= 1;
                        flag = 1;
                        break;
                    }
                    
                    if(flag) break;
                }
                if(count %2 == 0) count -= 1;
                res = max(res, count);
            }
        }
        
        return res;
    }
};

/*
問你說 要組成以某個字包夾的冪次數組 ex: 3 9 81 9 3 像這樣都是3的倍數的狀況的數組 並且他們的冪次是 0 2 4 8 16 每一次都比之前一次多兩倍
從給定數組中挑出subset 能夠符合條件的最長長度為多少
這題的陷阱是111111這種也要考量進去 並且如果他是偶數個只能取奇數個 因為要符合 3 9 3 這種形式 
[x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] k 可以是0 但必須是non-negative power of 2
k = 0 2 4 8 16 .... 
並且還需要考慮一下如果數字超過給定範圍1e9就可以不用找了 數字大小大約在2^30 所以我用一個跑30次的loop去算密次 但實際上數字超過2都不需要跑這麼多圈

choose number to satisfy 
[x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] k 可以是0 但必須是non-negative power of 2
k = 0 2 4 8 16 .... 
[2, 4, 8, 4, 2]
[4 16 64 16 4]
81 -> 9^2 or 3^4
去找每個數字有超過兩個的
[14,14,196,196,38416,38416] 14^4
*/
