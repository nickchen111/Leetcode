/*
2712. Minimum Cost to Make All Characters Equal
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    long long minimumCost(string s) {
        long long res = 0;
        int n = s.size();
        for(int i = 1; i < n; i++){
            if(s[i-1] != s[i]){
                if(i <= n-i){
                    res += i;
                }
                else res += (n-i);
            }
        }

        return res;
    }
};

/*

此題給你一個binary string 每一次你都可以讓左段或者右段區間翻轉  翻轉會有翻左段或者右段的cost
想讓你花最少的cost 讓所有區間變成 0 or 1
翻轉最自然的想法是選擇範圍不會交疊 要找分界點
最快的想法就是每次遇到相鄰不相同的元素 就看左邊cost少還是右邊 貪心的去翻他
1111011111011
0000111111011
0000111111100
x x x x x  i or n-i
假設是 0 1 先將左邊翻成 1 下一次如果再遇到 0 那就是左邊全體再翻i+1的cost
ex : 0 1 0 -> 1 + 2 (i = 1)
*/
