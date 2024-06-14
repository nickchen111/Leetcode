/*
3181. Maximum Total Reward Using Operations II
*/

// TC:O(n^2/64 + nlgn) SC:O(n)
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        set<int> set(rewardValues.begin(), rewardValues.end());
        vector<int> arr(set.begin(), set.end());
        bitset<100000> f{1};
        
        for(auto v : set){
            int shift = f.size()-v;
            f |= f << shift >> shift << v;
        }

        for(int i = arr.back()*2-1; ; i--){
            if(f.test(i)) return i;
        }

        return -1;
    }
};


/*
也就是想找一些子序列 他的總和都會比當前那個小 並且最大化所有數字總和
f[i][j] : 表示能否從前i個數 選出和為j的子序列
考慮v = rewardValues[i] 選or不選
選: f[i][j] = f[i][j-v] 0 <= j-v < v
不選: f[i][j] = f[i-1][j]

要想到都是往回看看當前rewardValues[i]-1之前的數字是否有 那就是前段的平移 可以用位運算加速!
因為如果表示成bit 可以用O(1)的時間計算出64個bit的OR
也就是說原本需要O(64)的時間被降到O(1) :)
原本是O(n^2) -> 5*1e9 現在可以除以64 5*1e9/ 64
c++因為有overflow問題 所以會有shift左shift右的方式將不要的那塊高位清掉 python可以直接 OR
*/
