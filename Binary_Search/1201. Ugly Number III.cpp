/*
1201. Ugly Number III
*/


// TC:O(lgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    int nthUglyNumber(int n, int a, int b, int c) {

        LL left = 1; LL right = 2e9;

        while(left < right){
            LL mid = left + (right -left)/2;
            if(check(mid,a,b,c) >= n) {
                right = mid;
            }
            else left = mid + 1;
        }

        return left;
    }

    int check(LL mid, LL a, LL b, LL c){
        return mid/a + mid/b + mid/c - mid/lcm(b,c) - mid/lcm(a,c) - mid/lcm(a,b) + mid/lcm(lcm(a,b),c);
    }
    
    LL lcm(LL a, LL b){
        return a*b/GCD(a,b);
    }
    LL GCD(LL a, LL b){
        if(b == 0) return a;
        return GCD(b, a%b);
    }
};
