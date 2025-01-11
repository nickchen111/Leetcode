// TC:O(n lglgn * ⍺(n)) SC:O(n)
class Solution {
public:
    vector<bool> areConnected(int n, int threshold, vector<vector<int>>& queries) {
        vector<int> pa(n+1);
        iota(pa.begin(), pa.end(),0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(rt != x) pa[x] = rt;
            return rt;
        };
        auto merge = [&](int x,int y) {
            x = find(x), y = find(y);
            if(x < y) pa[y] = x;
            else pa[x] = y;
        };
        vector<int> isPrime(n+1, 1);
        for(int i = threshold + 1; i <= n; i++) {
            if(isPrime[i]) {
                for(int p = i, q = 2*i; p <= n && q <= n; p += i, q += i) {
                    merge(p,q);
                    isPrime[q] = 0;
                }
            }
        }
        vector<bool> ans(queries.size());
        for(int i = 0; i < queries.size(); i++) {
            ans[i] = find(queries[i][0]) == find(queries[i][1]);
        }
        return ans;
    }
};

/*
這題要快速判斷兩個數字是否相通 肯定是要用UF
但要以什麼樣的標準UF兩個數字 
出想會是當他們之間共同可以被整除的數字超過threshold
1. 拿他們自己的質因數們 並且是否需統計頻率 
    a. 是 那就要計算各種不同的可能性 2:3, 3:2 -> 4*3種可能
    b. 否 
應該是藉由調和級數的概念 枚舉所有從threshold 到 n 的點 去讓他們merge起來自己的倍數 如此可以達到nlgn的速度
如果搭配埃式篩就是nlglgn
要想到這點主要是從UF出發 如果要相通的點肯定是兩個數字都要超過門檻值
所以重點在於將這些超過的數字union再一起
*/
