/*
190. Reverse Bits
*/

//TC:O(32) SC:O(1)
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = 0;
        for(int i = 0; i<32; i++){
            res = (res << 1) | (n & 1);
            n >>=1;
        }

        return res;
    }
};
/*
十進位做法 只能對正整數操作
ans = ans*10 + n%10; ans*10的部分一直將尾巴的數字往前推 取餘的部分不斷取尾巴的數字
n/=10;
二進位不用bit操作 只能對正整數操作 主要是因為n%2這邊會有差
ans = ans*2 + n%2;
n/=2;
且操作時要考慮到leading zero 也要合併在內 ex: 01100 -> 00110 not 011
負數的時候又疑補位是補1
正數捕0

改成位操作不管正負數皆可做
ans = (ans << 1) | (n & 1); 這裡|(or)的意思剛好會跟加一樣
n >>=1;

*/
