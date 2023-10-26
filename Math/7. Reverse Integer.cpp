/*
7. Reverse Integer
*/

// TC:O(lgn) 因為每次都除十 SC:O(1)
class Solution {
public:
    int reverse(int x) {
        int res = 0;
        while(x != 0){
            int digit = x%10;
            if(res > INT_MAX/10 || (res == INT_MAX/10 && digit > INT_MAX%10)){
                return 0;
            }
            if(res < INT_MIN/10 || (res == INT_MIN/10 && digit < INT_MIN%10)){
                return 0;
            }

            res = res*10 + digit;
            x/=10;
        }

        return res;
    }
};

//直接用abs判斷也可以
class Solution {
public:
    int reverse(int x) {
        int res = 0;
        while (x != 0) {
            if (abs(res) > INT_MAX/ 10) return 0;
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};
