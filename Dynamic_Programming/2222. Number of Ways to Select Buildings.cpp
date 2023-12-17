/*
2222. Number of Ways to Select Buildings
*/

// DP TC:O(n) SC:O(n*3*2)
class Solution {
    long long dp[100002][4][2];
public:
    long long numberOfWays(string s) {
        int n = s.size();
        s = "#" + s;
        dp[0][0][1] = 1;
        dp[0][0][0] = 1;//什麼都不選的狀況會有多少種可能
        for(int i = 1; i <= n; i++){
            for(int j = 0; j < 4; j++){
                for(int k = 0; k < 2; k++){
                    dp[i][j][k] = dp[i-1][j][k];//不選的狀況
                    if(j - 1 >= 0 && s[i]-'0' == k)
                        dp[i][j][k] += dp[i-1][j-1][1-k];
                }
            }
        }

        return dp[n][3][0] + dp[n][3][1];
    }
};

//Suffix + Binary Search :TC:O(n^2) at worst case SC:O(n)
class Solution {
    using LL = long long;
public:
    long long numberOfWays(string s) {
        int n = s.size();
        vector<LL> suf0(n);
        vector<LL> suf1(n);
        vector<int> pos1;
        vector<int> pos0;
        int count0 = 0;
        int count1 = 0;
        
        for(int i = n-1; i >= 0; i--){
            suf0[i] = count0;
            suf1[i] = count1;
            if(s[i] == '1'){
                count1 += 1;
                pos1.push_back(i);
            }
            else {
                count0 += 1;
                pos0.push_back(i);// 0 的位置
            }
        } 

        sort(pos0.begin(), pos0.end());
        sort(pos1.begin(), pos1.end());
       

        LL res = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '0'){
                //要取找他後面的1
                auto iter = upper_bound(pos1.begin(), pos1.end(), i);
                if(iter == pos1.end()) {
                    continue;
                }
                else {
                    for(auto p = iter; p < pos1.end(); p = next(p,1)){
                        res += suf0[*p];
                    }
                }
            }
            else if(s[i] == '1'){
                //要取找他後面的0
                auto iter = upper_bound(pos0.begin(), pos0.end(), i);
                if(iter == pos0.end()) {
                    continue;
                }
                else {
                    for(auto p = iter; p < pos0.end(); p = next(p,1)){
                        res += suf1[*p];
                    }
                }
            }
        }

        return res;
    }
};

/*
此題用 0代表辦公大樓 1代表餐廳 審查員要審查三個大樓 但為了保證多樣性 不能有連續兩個被選到的建築是相同的
問說有多少種選擇的方法
所以選了0下一個就是1 選了1下一個就是0
如果我選了一個1 or 0 後我可以知道後面還有多少種 0 or 1 並且他之後還有多少種 1 or 0 這三段相乘即為以某一個元素開頭的可能性
那就是紀錄一個後綴數組

DP: 這題的突破點還是在於 再考量要選哪些建築時 一定會跟前面的建築選什麼扯上關係 x x x x x i 
並且根據題意還需要考慮前面選了幾個建築 如果已經選了三個 當下也不用再選了 因此
dp[i] : 當下建築選或者不選的可能方案 [j]: 目前已經選了的建築數量 [k]: 當下選的建築是哪種類型 無腦將狀態加入維度
*/
