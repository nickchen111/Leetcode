/*
3388. Count Beautiful Splits in an Array
*/

// DP TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int beautifulSplits(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> lcp(n+1, vector<int>(n+1));
        for(int i = n-1; i >= 0; i--) {
            for(int j = n-1; j >= 0; j--) {
                if(nums[i] == nums[j]) {
                    lcp[i][j] = lcp[i+1][j+1] + 1;
                }
            }
        }
        int res = 0;
        for(int i = 1; i < n-1; i++) {
            for(int j = i + 1; j < n; j++) {
                if((i <= j-i && lcp[0][i] >= i) || (n-j >= j-i && lcp[j][i] >= j-i)) res += 1;
            }
        }
        
        return res;
    }
};

// 字符串哈希 也可以用z function TC:O(n^2) SC:O(n)
class Solution {
    using LL = long long;
public:
    int beautifulSplits(vector<int>& nums) {
        int n = nums.size();
        vector<LL> power(n+1);
        power[0] = 1;
        LL base = 499;
        LL MOD = 1e9+7;
        
        vector<LL> hash(n+1);
        for(int i = 0; i < n; i++){
            power[i+1] = (power[i]*base) % MOD;
            hash[i+1] = (hash[i]*base + (LL) nums[i]) % MOD;
        }
        auto sub_hash = [&](int l, int r){
            return ((hash[r] - hash[l] * power[r-l]) % MOD + MOD) % MOD;
        };
        // 枚舉斷點 第一部分 <= 第二部分長度 也就是 i <= j-i or 第三部分 >= 第二部分長度 -> n-j >= (j-i)
        int res = 0;
        for(int i = 1; i < n-1; i++) {
            for(int j = i + 1; j < n; j++) {
                if((i <= j-i && sub_hash(0, i) == sub_hash(i, i+i)) || (n-j >= j-i && sub_hash(j,j+j-i) == sub_hash(i, j))) {
                    res += 1;
                }
            }
        }
        
        return res;
    }
};

/*
分成三個部分 第二個部分的前綴要是第一個部分整體 or 第三個部分前綴要是第二個部分整體
我想到的是 枚舉中間斷點 然後看是否前面or 後面吻合
1. 當目前的第二部分跟第一個部分吻合 就去找下一個長度len*2
2. 當目前第二部分跟第一部分不吻合 就持續擴大長度 直到跟第三部分吻合 如果都不吻合 就在去做1
匹配部分使用字符串哈希
*/
