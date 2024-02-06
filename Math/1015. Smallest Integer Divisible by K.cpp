/*
1015. Smallest Integer Divisible by K
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int smallestRepunitDivByK(int k) {
        
        int num = 1;
        int count = 1;
        unordered_set<int> set;
        while(1){
            if(num%k == 0) return count;
            if(set.find(num%k) != set.end()) return -1;
            set.insert(num%k);
            num = (num*10+1)%k;
            count++;
        }

        return -1;
    }
};

/*
找到一個最小的正整數n 可以被 k整除 而且n只能由1組成
如果沒有這個數返回-1
1 <= k <= 10^5
1 11 111 1111 11111
要整除啥的要想到餘數
去看看11 111 1111這些有什麼關係
x1 = k*q + r1
x2 = 10x1 + 1 -> 10r1 + 1 = r2(mod k)
x3 = 10r2 + 1 (mod k) -> r3
並且一個數字一直去*10+1然後對某個數字取餘會有循環結如果都不是0並且繞回去就返回-1
*/
