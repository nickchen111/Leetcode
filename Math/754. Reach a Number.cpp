/*
754. Reach a Number
*/

//TC:O(n) SC:O(1)
class Solution {
public:
    int reachNumber(int target) {
        int sum = 0;
        int step = 0;
        target = abs(target);
        while(!(sum >= target && (sum-target) % 2 ==0)){
            step += 1;
            sum += step;
        }

        return step;
    }
};

/*
這題就是之前的一維數組走路徑到target的變型
改成說你每次能走的步數變成當下回合數數字 一樣是可以走左or走右 問說最少幾步可以走到終點
-10^9 <= target <= 10^9 ->這個範圍也沒辦法開數組做dp
所以看到這個數據範圍要想想看lgn解法 binary search
target != 0
-3 -2 -1 0 1 2 3 
數學上來說就是 0 1 2 3 4 5 6 7 ....中間運算符可以是+ or - 利用最少的數字加到target

((n+1)*n)/2
1 step 1
0-1 = -1
0+1 = 1

2 step 1 3 
0-1+2 = 1
0-1-2 = -3
0+1+2 = 3
0+1-2 = -1

3step 2 4 6 
0-1-2-3 = -6
0-1-2+3 = 0
0-1+2-3 = -2
0-1+2+3 = 4
0+1-2-3 = -4
0+1+2+3 = 6
0+1-2+3 = 2
0+1+2-3 = 0

4step 2 4 6 8 10
0+1+2+3+4 = 10
0+1+2+3-4 = 2
0+1+2-3+4 = 4
0+1+2-3-4 = -4
0+1-2+3+4 = 6
0+1-2-3-4 = -8

5 step 1 3 5 7 9 11 13 15
6 step 1 3 5 7 9 11 13 15 17 19 21
7 step 2 4 6 8 10 12 14 16 18 20 22 24 26 28 

Binary search 經過分析會長上述形式 但是如果要求的數字小於當下總和 而且total - target % 2 != 0匙會不知道該往哪走
ex : step4 total = 10 target = 5 or 3 兩個完全不同方向
所以不能用binary search 要遍歷逐步的累加 當sum < target && (sum - target)%2 != 0就要一直走下去
*/
