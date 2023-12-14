/*
2364. Count Number of Bad Pairs
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        int n = nums.size();
        
        unordered_map<int,long long> map;
        for(int i = 0; i < n; i++){
            map[nums[i] - i] += 1;
        }

        long long res = 0;
        for(auto p:map){ 
            res += (long long)(n - p.second) * (p.second);
        }
        res /= 2;
        
        return res;
    }
};

/*
算有多少個pair在數組裡符合
bad pair if i < j and j - i != nums[j] - nums[i].
nums[i] - i != nums[j] - j
[2 3 2 4 2 3 4]
原本想開數組紀錄 然後遍歷過程開始看之前的元素 by Bibary search去找嘗試計算每走一步有多少個跟他不同的 但感覺會要考慮蠻多狀況
並且也不曉得跟他相同的有幾個 如果都一樣那就每次lower_bound完都要往前往後遍歷
不如用map記錄種類 然後以知數組長度 就可以用簡單加減乘除計算出來 最後記得要除2 因為會重複計算
[4,1,3,3] -> [4 2 5 6]
[0 1 2 3]
*/
