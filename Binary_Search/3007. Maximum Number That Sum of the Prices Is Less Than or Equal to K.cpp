/*
3007. Maximum Number That Sum of the Prices Is Less Than or Equal to K
*/

// TC:O(50*50*lgn) SC:O(50)
class Solution {
    using LL = long long;
public:
    long long findMaximumNumber(long long k, int x) {
        LL left = 1, right = 1e15;
        while(left < right){
            LL mid = left + (right - left + 1) / 2;
            if(check(mid,k,x)) left = mid;
            else right = mid - 1;
        }

        return left;
    }
    bool check(LL A, LL k, int x){

        LL res = 0;
        //改成0 index
        for(int i = x-1; (1LL<<i) <= A; i+=x){
            
            //先將數字做處理
            LL a = A;
            vector<int> arr;
            //得出來的會是大的在右邊 小的在左邊
            while(a > 0){
                arr.push_back(a%2);
                a /= 2;
            }

            LL X = 0;
            if(arr[i] == 0){
                for(int j = arr.size()-1; j > i; j--){
                    X = X*2 + arr[j];
                }
                res += X*pow(2,i);
            }
            else {
                for(int j = arr.size()-1; j > i; j--){
                    X = X*2 + arr[j];
                }
                res += X*pow(2,i); 

                LL Y = 0;
                for(int j = i-1; j >= 0; j--){
                    Y = Y*2 + arr[j];
                }
                res += (Y+1);
            }
            if(res > k) return false;
        }

        return true;
    }
};


/*
此題首先看出是二分搜索 然後如果有做過233題就會寫這題
這題的首要思維並不是給你個數你來數有多少個1 而是 有哪些是可以在某個位置上放1
1 - num 的所有數字 他們的 右邊數過來1-index ith位 要 % x == 0   並且那個位置要放１
然後加總有1的數字 總量不能超過k
這題要先看出數字如果越大就越難符合 1的總數是 <= K的條件 所以具有單調性
再來就是用到233題的技巧 數1在某個位置有多少種符合的可能性
A=> compute all price for 1,2,3,.... A
A    X X X 0 Y Y Y 左邊是高位右邊低位
           1
000~(XXX-1)   000 ~ (2^t) => XXX*2^t

A    X X X 1 Y Y Y 
           1
兩種情況 
    X X X    000 ~ YYY => 1*(YYY+1)
000 ~ (XXX-1)  000 ~ 111 => XXX*2^t

arr : Y Y Y i X X X
x x x x x x 7 x x x x x x 14 x 
            6+7           13
*/
