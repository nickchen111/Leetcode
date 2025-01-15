// TC:O(max(m,n)) SC:O(1)
class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int cnt2 = __builtin_popcount(num2); // 需要設置的1數量
        int cnt1 = __builtin_popcount(num1); // 可抵銷的1數量
        if(cnt2 == cnt1) return num1;

        int res = 0;
        int cnt = 0;
        while(cnt2 && num1) {
            if((num1 & 1) && cnt2 >= cnt1) {
                cnt1 -= 1;
                cnt2 -= 1;
                res |= (1 << cnt);
            }
            else if((num1 & 1) == 0 && cnt2 > cnt1) {
                res |= (1 << cnt);
                cnt2 -= 1;
            }
            else if((num1 & 1)) cnt1 -= 1;
            cnt += 1;
            num1 >>= 1;
        }
        while(cnt2) {
            res |= (1 << cnt);
            cnt += 1;
            cnt2 -= 1;
        }
        return res;
    }
};
