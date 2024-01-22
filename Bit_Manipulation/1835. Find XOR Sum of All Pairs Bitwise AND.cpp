/*
1835. Find XOR Sum of All Pairs Bitwise AND
*/

// TC:O(32*m + 32*n) SC:O(32)
class Solution {
    using LL = long long;
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        LL m = arr1.size(); 
        LL n = arr2.size();
        vector<LL> count1(32);
        vector<LL> count2(32);
        for(int i = 0; i < m; i++){
            int cur = arr1[i];
            for(int j = 0; j < 32; j++){
                int d = cur&1;
                if(d == 1) count1[j] += 1;
                cur >>= 1;
                if(cur == 0) break;
            }
        }
        for(int i = 0; i < n; i++){
            int cur = arr2[i];
            for(int j = 0; j < 32; j++){
                int d = cur&1;
                if(d == 1) count2[j] += 1;
                cur >>= 1;
                if(cur == 0) break;
            }
        }

       
        vector<LL> count_1(32);
        int res = 0;
        for(int i = 0; i < 32; i++){
            count_1[i] = count1[i]*count2[i];
        }

        for(int i = 0; i < 32; i++){
            if(count_1[i] % 2 == 1) res += (1<<i);
        }

        return res;
    }
};

/*
此題說如果數組只有一個元素那XOR sum就是他自己
現在給你兩個數組 你還需要先做一件事 將所有的pair對@兩個數組做 AND
最後求兩個數組每一對pair做完AND之後XOR的結果
偶數次的 0 偶數次 1
00 11 -> 0
偶數次的 0 奇數次 1
00 111 -> 1
奇數次 0 奇數次 1
000 111 -> 1
奇數次0 偶數次1 
0 11 -> 0
4 ->  0100
12 -> 1100

arr1 每個位置上1的位置數量
arr2 每個位置上1的位置數量
兩者相乘 就會是當下&之後能夠留下的數量 其他的就是m*n-乘積量 的0

*/
