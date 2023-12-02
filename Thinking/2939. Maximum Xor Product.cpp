/*
2939. Maximum Xor Product
*/


// TC:O(n) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int maximumXorProduct(long long a, long long b, int n) {
        LL A = a >> n;
        LL B = b >> n;
        if(A < B) return maximumXorProduct(b,a,n);

        if(A > B){
            for(int k = n-1; k>=0; k--){
                LL bit1 = (a >> k)&1;
                LL bit2 = (b >> k)&1;
                if(bit1 == bit2){
                    //通通改成1
                    a = a - (bit1 << k) + (1LL << k);
                    b = b - (bit2 << k) + (1LL << k);
                }
                else {
                    //將1放在較小的那個數字上
                    a = a - (bit1 << k);
                    b = b - (bit2 << k) + (1LL << k);
                }
            }
        }
        else {
            bool flag = 0;
            for(int k = n-1; k>=0; k--){
                LL bit1 = (a >> k)&1;
                LL bit2 = (b >> k)&1;
                if(bit1 == bit2){
                    //通通改成1
                    a = a - (bit1 << k) + (1LL << k);
                    b = b - (bit2 << k) + (1LL << k);
                }
                else {
                    if(flag == 0){
                        a = a - (bit1 << k) + (1LL << k);
                        b = b - (bit2 << k);
                        flag = 1;
                    }
                    else {
                        a = a - (bit1 << k);
                        b = b - (bit2 << k) + (1LL << k);
                    }
                }
            }
        }

        return ((a%M)*(b%M))%M;
    }
};

/*
a: 0.  1.  1   0
b: 1.  0.  1.  0
x: 0 1 0 1 0 1 0 1
--------------- 
   0 1 1 0 1 0 0 1
   1 0 0 1 1 0 0 1
所以當a b all = 1 x -> 0 a b all = 0 x -> 1
maxmize (a*b) given fixed a+b => a=b
且分兩種情況討論 如果n的範圍可以包含到a b所有位數
且 a b 遇到 10狀況 那就先改一個後面就都改另一個
如果無法涵蓋所有 那就看a b前段誰大 小的可以獲得所有的1
*/
