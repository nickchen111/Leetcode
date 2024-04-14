/*
3116. Kth Smallest Amount With Single Denomination Combination
*/

// TC:O(32*m*O(sum of C(n,k))) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long findKthSmallest(vector<int>& coins, int k) {
         LL left = 1, right = 51e9;
        while (left < right)
        {
            LL mid = left+(right-left)/2;
            if (isOK(coins, mid, k))
                right = mid;
            else
                left = mid+1;
        }
        
        return left;
    }
    bool isOK(vector<int>& coins, LL mid, int t){
        int m = coins.size();
        LL res = 0;
        int sign = 1;
        for(int k = 1; k <= m; k++){
            int state = (1<<k) -1;
            LL sum = 0;
            while(state < (1<<m)){
                LL product = 1;
                for(int i = 0; i < m; i++){
                    if((state >> i)&1) {
                        product = product * coins[i] / gcd(product, coins[i]);
                    }
                }
                sum += (mid/product);
                
                int c = state&-state;
                int r = state + c;
                state = (((r^state)>>2)/c ) | r;
            }
            
            res += sign*sum;
            sign*=-1;
        }
        
        return res >= t;
        
    }
};


/*
這題是1201 ugly numberII的進階題 需要考慮的數字太多了 單純公式沒辦法完全處理容斥原理 需要用到bit運算去列舉所有可能子集合 然後搭配公式的邏輯
+-+-+-...這樣下去 例如有三個數字的話就會是 一個數字的狀態 - 兩個數字的狀態 + 三個數字的狀態
*/
