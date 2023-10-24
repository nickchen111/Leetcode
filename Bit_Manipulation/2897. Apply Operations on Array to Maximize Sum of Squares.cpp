/*
2897. Apply Operations on Array to Maximize Sum of Squares
*/

//TC:O(nk) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int maxSum(vector<int>& nums, int k) {
        vector<int> bit(32,0);
        for(auto x:nums){
            for(int i = 0; i<32; i++){
                //有一的話就++
                if((x>>i)&1){
                    bit[i]++;
                }
            }
        }

        LL res = 0;
        for(int t = 0; t<k; t++){
            LL x = 0;
            for(int i = 31; i>=0; i--){
                if(bit[i] > 0){
                    x+=(1LL<<i);
                    bit[i]--;
                    x%=M;
                }
            }
            res += x*x%M;
            res%=M;
        }

        return res;
    }
};

/*
此題為greedy + bit operation
意思就是可以對彼特位上的數字做 AND 跟 OR操作
X Y => AND OR
1 0.    0  1
0 0.    0. 0
1 1.    1. 1
0 1.    0  1
上述就是要用貪心去實現
也就是說and會變小 or會變大 
然後要去選最大的k個element 去求他們的平方和
就是把所有的數字改將比特表示 然後開始拼湊出他們最大的可能性
*/
