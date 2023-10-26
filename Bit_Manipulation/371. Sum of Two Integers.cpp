/*
371. Sum of Two Integers
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int getSum(int a, int b) {
        if(a == 0) return b;
        if(b == 0) return a;
        while(b!=0){
            int carry = a&b;//去分出進位的數字出來
            a = a^b;//計算出沒有進位時的狀況 如果有進位下次循環的時候這裡會去進位
            b = carry<<1;//看看還有多少位要進
        }
        return a;
    }
};

/*
16 84
carry = 0010000 & 1010100 = 0010000->16
a = 0010000^1010100 -> 1000100-> 64+4 = 68
b = 0100000

下一次 
carry = 1000100 & 0100000-> 000000->0
a = 1000100^0100000 -> 1100100->64+32+4=100
*/
