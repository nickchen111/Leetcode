/*
354. Russian Doll Envelopes
*/

//用dp time : o(n ^2) 會TLE
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(envelopes.begin(), envelopes.end(), [](vector<int>& a, vector<int>& b){
            if(a[0] == b[0]){//寬度一樣的時候 高度按降序排序
                return a[1] > b[1];
            }
            else return a[0] < b[0];//寬度按升序 確保肯定裝得下
        });

        //將高度數組單獨保存起來
        vector<int> heigh(n);
        for(int i = 0; i < n; i++){
            heigh[i] = envelopes[i][1];
        }

        return lenghtofLIS(heigh);
    }

    int lenghtofLIS(vector<int>& heigh){
        // base case
        vector<int> dp(heigh.size(), 1); //去對應heigh數組每個當下最長遞增子序列
        //去計算摟～～狀態轉移方程 for dp數組
        for(int i = 0; i < heigh.size(); i++){
            for(int j = 0; j < i; j++){
                if(heigh[i] > heigh[j]){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < dp.size(); i++){
            ans = max(ans, dp[i]);
        }

        return ans;
    }
};

//用greedy algo o (nlgn)
class Solution {
    //greedy
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        sort(envelopes.begin(), envelopes.end(), [](vector<int>& a, vector<int>& b){
            if(a[0] == b[0]){//寬度一樣的時候 高度按降序排序
                return a[1] > b[1];
            }
            else return a[0] < b[0];//寬度按升序 確保肯定裝得下
        });

        vector<int> q;
        for(auto x:envelopes){
            if(q.empty() || x[1] > q.back()){
                q.push_back(x[1]);
            }
            else{
                auto iter = lower_bound(q.begin(), q.end(), x[1]);
                * iter = x[1];
            }
        }
        return q.size();
    }

};

/*
此題為最長遞增子序列 題目300題轉成二維的狀況題
dp: TLE
先对宽度 w 进行升序排序，如果遇到 w 相同的情况，则按照高度 h 降序排序。
之后把所有的 h 作为一个数组，在这个数组上计算 LIS 的长度就是答案。
tc: o(n^2) sc: o(n)也可以不用高度數組 變o(1)

greedy:
先对宽度 w 进行升序排序，如果遇到 w 相同的情况，则按照高度 h 降序排序。
就變成單純求LIS 還可以用greedy求解 更快
单纯求解宽度数组的LIS序列，就可以用o(NlogN)的贪心解法了
tc: o(nlgn) 不論sort or lower_bound 二分查找都是nlgn sc: o(n)

ps:
如果新的信封高度小於等於 q 的最後一個元素，則使用二分查找找到 q 中第一個大於等於這個高度的元素，
並將其替換為新的信封高度。這麼做的目的是保持 q 數組的遞增性質，同時確保新的信封高度能夠被選擇進行嵌套。
*/
