/*
3287. Find the Maximum Sequence Value of Array
*/

// TC:O(n*2^7*2^7) SC:O(n*2^7)
class Solution {
public:
    int maxValue(vector<int>& nums, int k) {
        const int MX = 1 << 7;
        int n = nums.size();
        vector<array<int,MX>> suf(n);
        vector<array<int,MX>> f(k+1);
        f[0][0] = true;// 選了0個得到0為true
        for(int i = n-1; i >= k; i--) {
            for(int j = min(k-1, n-1-i); j >= 0; j--) {
                for(int x = 0; x < MX; x++) {
                    if(f[j][x]) {
                        f[j+1][x|nums[i]] = 1;
                    }
                }
            }
            if(i <= n-k) {
                suf[i] = f[k];
            }
        }
        vector<array<int,MX>> pre(k+1);
        pre[0][0] = true;
        int res = 0;
        for(int i = 0; i < n-k; i++) {
            for(int j = min(i,k-1); j >= 0; j--) {
                for(int x = 0; x < MX; x++) {
                    if(pre[j][x]) {
                        pre[j+1][x|nums[i]] = 1;
                    }
                }
            }

            if(i < k-1) continue;
            for(int x = 0; x < MX; x++) {
                if(pre[k][x]) {
                    for(int y = 0; y < MX; y++) {
                        if(suf[i+1][y]) {
                            res = max(res, x^y);
                        }
                    }
                }
            }
        }

        return res;
    }
};

/*
左k 右k 個的OR 
OR 越來越大 
XOR 相同為0不同為1
問說兩邊XOR最大的數值是多少
n^3可接受
暴力 分隔線一個 左邊選k個cn取k 右邊也ｃn取k 枚舉所有可能
因為此題nums[i] 最多就是2^7-1 所以不可能OR到超過這個數字 那可以假設走到某個位置的時候選了j個數字 可以組成x的可能性
就可以前後綴分解了

難點1: 想到前後綴分解 枚舉左邊與右邊的可能性
難點2: 怎麼算所有OR運算可能性
難點3: 想到此題OR與01背包類似特性，但是只會模板的還是做不出來 會發現查表法不好做 已知10 跟當前物品3 需要看之前有無7, 但這題要用刷表法，就是利用已知去推導出未知更好做 (不好做原因 你要怎麼去推當前數字是某個數字OR之後才有當前數字)
因為這題數字範圍只從1-128 所以可以用狀態壓縮把出現的數字紀錄起來 suf[i][j][k] 能否從後i個數選j個數得出k的數值來
選 or 不選
suf[i][j][k] = suf[i+1][j-1][k] 不選
suf[i][j][k|v] = suf[i+1][j][k|v] or suf[i+1][j-1][k]
*/
