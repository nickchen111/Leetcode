/*
1702. Maximum Binary String After Change
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    string maximumBinaryString(string binary) {
        int n = binary.size();
        int count0 = 0;
        int count1 = 0;
        string res = "";
        bool flag = 1;
        for(int i = 0; i < n; i++){
            //開頭就是1不用去動它
            if(flag && binary[i] == '1') res += "1";
            else if(flag == 0 && binary[i] == '1') count1 += 1;
            else if(flag && binary[i] == '0'){
                count0 += 1;
                flag = 0;
            }
            else if(flag == 0 && binary[i] == '0'){
                count0 += 1;
            }
        }

        if(count0 <= 1) return binary;
        
        while(count0 - 1 > 0){
            res += "1";
            count0 -= 1;
        }
        res += "0";
        while(count1 > 0){
            res += "1";
            count1 -= 1;
        }

        return res;

    }
};

/*
1. 00 -> 10
2. 10 -> 01
盡量讓此binary string最大化

所以我要看的是 除了leading 1後面開始有多少個0 將他都移過來變成m-1個1再補上一個0
但如果都沒有0 or 只有一個0那就是直接返回原string
0000到1為止可以變 11101...
111到0為止可以變 -> 0111
*/
