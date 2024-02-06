/*
1526. Minimum Number of Increments on Subarrays to Form a Target Array
*/


// TC:O(n) SC:O(n) -> O(1)
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int n = target.size();
        int res = 0;
        stack<int> stack;
        for(int i = 0; i < n; i++){
            if(!stack.empty() && target[stack.top()] > target[i]){
                res += (target[stack.top()] - target[i]);
                
            }
            stack.push(i);
        }

        res += target[stack.top()];
        return res;
    }
};

/*
有一個target數組 你要從initial全部都是0開始 每一次可以在一個區間每個元素增加1
問最少做幾次操作讓她變得跟target一樣
[1 2 3 2 1]
[1 5 2 4 3] ->[0 4 1 3 2] -> [0 3 0 2 1] -> + 3 + 2
其實就是單調遞增的序列 如果遇到遞減狀況 就需要先去扣掉較大的那塊多餘的次數就可以pop掉繼續往後遞增
然後最後剩下的最大的數字他所需要的次數肯定可以cover掉他前面較小的數字
[3,1,4,4,2]
*/
