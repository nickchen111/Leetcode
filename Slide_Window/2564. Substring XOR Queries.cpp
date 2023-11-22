/*
2564. Substring XOR Queries
*/

// Slide Window TC:O(31*m) SC:O(n) m 為字串長度 n為query次數
class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        unordered_map<int,vector<int>> map;
        for(int i = 0; i<queries.size(); i++){
            map[queries[i][0]^queries[i][1]].push_back(i);
        }

        vector<vector<int>> res(queries.size(),{-1,-1});
        //因為query的二進位長度必定為31以內 所以可以用固定長度滑窗來判斷有無數值
        for(int len = 1; len<=31; len++){
            long long sum = 0;
            for(int i = 0; i<s.size(); i++){
                sum = sum*2 + (s[i]-'0');
                if(i-len >= 0){
                    sum-=(1LL<<len)*(s[i-len]-'0');
                }

                if(map.find(sum) != map.end()){
                    for(auto idx:map[sum]){
                        if(res[idx][0] != -1){
                            break;
                        }
                        res[idx] = {i-len+1,i};
                    }
                }
            }
        }
        return res;
    }
};


// KMP TLE 寫法跟1764題一樣 TC:O(m+n)->10^5*(32*m) query次數太多了 滑動窗口的做法直接以空間換時間
class Solution {
public:
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) {
        int n = queries.size();
        vector<string> self;
        for(auto query:queries){
            int cur = query[0]^query[1];
            string curStr = "";
            while(cur != 0){
                int num = cur&1;
                cur = cur>>1;
                curStr = to_string(num) + curStr;
            }
            if(curStr == "") self.push_back("0");
            else self.push_back(curStr);
        }
        //將每個字符串轉成lsp存起來

        vector<vector<int>> lsp = preprocessor(self);
        vector<vector<int>> res;
        for(int k = 0; k<lsp.size(); k++){
            int m = s.size();
            vector<int> dp(m);
            bool flag = false;
            int len = self[k].size();//模式串長度
            dp[0] = (s[0] == self[k][0]);
            if(dp[0] == len){
                res.push_back({0,0});
                continue;
            }
            for(int i = 1; i<m; i++){
                int j = dp[i-1];
                while( j > 0 && s[i] != self[k][j]){
                    j = lsp[k][j-1];
                }
                dp[i] = j + (s[i] == self[k][j]);
                if(dp[i] == len){
                    res.push_back({i-len+1,i});
                    flag = true;
                    break;
                }
            }
            if(flag) continue;
            else res.push_back({-1,-1});
            
        }

        return res;
    }
    vector<vector<int>> preprocessor(vector<string>& self){
        vector<vector<int>> res;
        for(int k = 0; k<self.size(); k++){
            int n = self[k].size();
            vector<int> suf(n);
            suf[0] = 0;
            for(int i = 1; i<n; i++){
                int j = suf[i-1];
                while( j > 0 && self[k][i] != self[k][j]){
                    j = suf[j-1];
                }
                suf[i] = j + (self[k][i] == self[k][j]);
            }
            res.push_back(suf);
        }
        return res;
    }
};


/*
010 ! 101 -> 111
2 ! 5 = 7
x ! 1 = 2;
011 001 010 OR?
101    111 010 -> 101 代表自己要先XOR

O(31N)的方法
110 (1) -> 110*2+1-1*2(3);
110 (1) -> 110*2+(1&1) - (1<<len)*(s[i-len]-'0');
*/
