/*
2457. Minimum Addition to Make Integer Beautiful
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    long long makeIntegerBeautiful(long long n, int target) {
        string res = "";
        int carry = 0;
        while(n > 0){
            if(check(n) <= target) break;
            int cur = n % 10;
            
            if(cur == 0) {
                res.push_back('0');
                carry = 0;
            }
            else {
                res.push_back(10 - cur + '0');
                carry = 1;
            }

            n = n/10 + carry;
        }

        if(res.empty()) return 0;
        reverse(res.begin(), res.end());
        
        long long ret = stoll(res);

        return ret;
    }

    int check(long long n){
        int sum = 0;
        while(n){
            sum += (n%10);
            n /= 10;
        }

        return sum;
    }
};

/*
此題想讓一個整數內所有數字加總小於target 問說最少需要加多少大小的數字
很明顯的貪心策略 通常都從最小的開始加 注意一些條件
1. if當前數字已經是0 那麼直接答案後面加0
2. 注意進位 每加入一個數字後要進位
每次做完操作後都去判斷一下是否符合條件了 
*/
