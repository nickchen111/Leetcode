/*
357. Count Numbers with Unique Digits
*/

// TC:O(n^2) SC:O(1)
class Solution {
public:
    int countNumbersWithUniqueDigits(int n) {
        int res = 1; // 因為這題需要包含 0
        for(int len = 1; len <= n; len++){
            res += A(10,len) - A(9,len-1);
        }

        return res;
    }
    int A(int m, int n){
        int count = 1;
        for(int i = 0; i < n; i++){
            count *= (m-i);
        }

        return count;
    }
};

/*
就去看每個長度上 可以組成多少種組合 但不能有leading zero的狀況下
*/
