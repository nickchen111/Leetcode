/*
3008. Find Beautiful Indices in the Given Array II
*/


// KMP TC:O(n+m + n+k+ mlgk) SC:O(n)
class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        // KMP
        vector<int> idx1 = KMP(s,a);// string a pos
        vector<int> idx2 = KMP(s,b); // string b pos
        int n = s.size();
       
        vector<int> res;
        for(int i : idx1){
            // i-k = 2-3, j = 0, 2+3 = 5 -> idx2.end() - idx2.begin();
            auto iter2 = upper_bound(idx2.begin(), idx2.end(), i+k);
            auto iter1 = lower_bound(idx2.begin(), idx2.end(), i-k);
            // i = 0 j = 4, k = 3
            if(iter2 - iter1 >= 1) res.push_back(i);
            
        }
        
        
        return res;

        
    }
    vector<int> KMP(string& p, string& s){
        int n = p.size();
        int m = s.size();
        if(m == 0) return {};
        if(n == 0) return {};
        vector<int> suf = preprocessor(s);
        vector<int> dp(n);
        dp[0] = (p[0] == s[0]);
        vector<int> res;
        if(dp[0] == m){
            res.push_back(0);
        }
        for(int i = 1; i < n; i++){
            int j = dp[i-1];
            while(j > 0 && p[i] != s[j]){
                j = suf[j-1];
            }
            dp[i] = j + (p[i] == s[j]);
            if(dp[i] == s.size()){
                res.push_back(i-s.size()+1);
            }
        }
        
        return res;
        
    }

    vector<int> preprocessor(string& p){
        int n = p.size();
        vector<int> dp(n,0);
        for(int i=1; i<n;i++){
            int j = dp[i-1];
            while(j > 0 && p[i] != p[j]){
               j = dp[j-1];
            }
            dp[i] = j+(p[i] == p[j]);
        }

        return dp;
    }
};

// 字符串搜索暴力解 TC:O(10*n + mlgm + klgk + m*k) SC:O(m+k) 
class Solution {
public:
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        int n = s.size();
        set<int> setA;
        set<int> setB;
        int m = a.size();
        // len = 4, m = 2 0 1 2 3
        for(int i = 0; i < n-m+1; i++){
            string str = s.substr(i, m);
            if(str == a) setA.insert(i);
        }
        int t = b.size();
        for(int i = 0; i < n-t+1; i++){
            string str = s.substr(i, t);
            if(str == b) setB.insert(i);
        }
        
        vector<int> res;
        for(auto p : setA){
            for(auto q : setB){
                if(abs(q-p) <= k){
                    res.push_back(p);
                    break;
                }
            }
        }
        
        return res;
        
    }
};


/*
這題要你在一個大字串中 找兩個字串是否在大字串裡頭 並且問說 小字串i index 跟小字串j的index |j-i| 是否小於等於k
KMP先找出兩個字串相同之處 在用Binary Search判斷i+k >= j ~ i-k <= j的區間
i-k <= j && i+k >= j 沒想通的點 要是兩個都符合就會是答案 不能只符合一個
例如這個case i = 0, j = 4, k =3  兩個都會找到.begin()上的點 但其實他是out of boundary的
*/
