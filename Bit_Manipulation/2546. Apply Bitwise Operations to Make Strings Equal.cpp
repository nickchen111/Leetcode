/*
2546. Apply Bitwise Operations to Make Strings Equal
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    bool makeStringsEqual(string s, string target) {
        int n = s.size();
        int count1 = 0;
        int count2 = 0;
        for(int i = 0; i < n; i++){
            if(target[i] == '1') count2 += 1;
            if(s[i] == '1') count1 += 1;
        }
        if(count2 && count1) return true;
        else if(count2 == 0 && count1 == 0) return true;
        else if(count2 == 0 && count1 != 0) return false;
        else return false;

        
    }
};

/*
此題說每次操作可以挑兩個元素作 s[i] OR s[j] 以及 s[i] XOR s[j]
OR:
1 1 -> 1
0 1 -> 1
1 0 -> 1
0 0 -> 0

XOR
1 1 -> 0
0 1 -> 1
1 0 -> 1
0 0 -> 0
看得出來如果只做 00操作會是沒有意義的 首要之物是先算出1 0有幾個
1 0這種case 只能增加1 
11 這種case 可以減少1增加0
00 這種case沒意義
s = "1010", target = "0110"
1 1 0 1 1 -> 0 0 0 0 1 只有在target沒有1 自己有一的狀況下 是不可能
此題只求有沒有可能 換句話說 某一方為0個1 另一方有1 就會做不到
*/
