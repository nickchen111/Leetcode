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


// 更直觀一點的解法 
using LL = long long;
class Solution {
public:
    long long minimumCost(string s) 
    {
        LL ret1 = solve(s);
        for (int i=0; i<s.size(); i++)
            if (s[i]=='1')
                s[i]='0';
            else
                s[i]='1';
        LL ret2 = solve(s);
        return min(ret1,ret2);
    }
    
    LL solve(string s)
    {
        int n = s.size();
        vector<LL>left(n);
        
        LL sum = 0;
        for (int i=0; i<n; i++)
        {
            if (s[i]=='0')
            {
                left[i] = sum;
                continue;                
            }
            
            if (i>=1 && s[i-1]=='1')
                sum = sum+1;
            else
                sum += (i+1) + i;

            left[i] = sum;
            
        }
        
        vector<LL>right(n);
        
        sum = 0;
        for (int i=n-1; i>=0; i--)
        {
            if (s[i]=='0')
            {
                right[i] = sum;
                continue;                
            }
            
            if (i+1<n && s[i+1]=='1')
                sum  = sum+1;
            else
                sum += (n-i) + (n-i-1);
            right[i] = sum;
        }
        
        LL ret = right[0];
        for (int i=0; i<n-1; i++)
            ret = min(ret, left[i]+right[i+1]);
        return ret;
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
