/*
3327. Check if DFS Strings Are Palindromes
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> next(n);
        for(int i = 1; i < n; i++) {
            // 由于 i 是递增的，所以 g[p] 必然是有序的，下面无需排序
            next[parent[i]].push_back(i);
        }
        
        string dfsStr(n,0);
        int time = 0;
        vector<pair<int,int>> node(n);
        function<void(int)> DFS = [&](int x) -> void {
            node[x].first = time;
            for(auto &y : next[x]) {
                DFS(y);
            }
            dfsStr[time++] = s[x]; // 後序遍歷
            node[x].second = time;
        };
        DFS(0);
        
        string t = "#";
        for(auto &ch : dfsStr) {
            t += ch;
            t += "#";
        }
        
        int m = t.size();
        vector<int> halfLen(m);
        // # x # x # x # x # x # x #
        for(int i = 0, c = 0, r = 0, len; i < m; i++) {
            len = r > i ? min(halfLen[2*c-i], r-i) : 1;
            while(i + len < m && i - len >= 0 && t[i-len] == t[i+len]) {
                len ++;
            }
            if(i + len > r) {
                r = i + len;
                c = i;
            }
            halfLen[i] = len;
        }
        
        auto isPalindrome = [&](int l, int r) -> bool {
            return halfLen[l+r] > r - l;
        };
        
        vector<bool> res(n);
        for(int i = 0; i < n; i++) {
            res[i] = isPalindrome(node[i].first, node[i].second);
        }
        
        return res;
    }
};

// 字符串哈希 TC:O(2*n) SC:O(2*n)
class Solution {
    using LL = long long;
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> next(n);
        for(int i = 1; i < n; i++) {
            next[parent[i]].push_back(i);
        }
        
        string dfsStr(n,' ');
        int time = 0;
        vector<pair<int,int>> node(n);
        function<void(int)> DFS = [&](int x) -> void {
            node[x].first = time;
            for(auto &y : next[x]) {
                DFS(y);
            }
            dfsStr[time++] = s[x];
            node[x].second = time;
        };
        DFS(0);
        
        vector<LL> power(n+1);
        power[0] = 1;
        LL base = 499;
        LL MOD = 1e9+7;
        
        vector<LL> hash1(n+1);
        vector<LL> hash2(n+1);
        
        string t = dfsStr;
        reverse(t.begin(), t.end());
        for(int i = 0; i < n; i++) {
            power[i+1] = (power[i]*base) % MOD;
            hash1[i+1] = (hash1[i]*base + (LL) dfsStr[i]) % MOD;
            hash2[i+1] = (hash2[i]*base + (LL) t[i]) % MOD;
        }

        function<int(int l, int r)> subhash1 = [&](int l, int r) -> int {
            return ((hash1[r] - hash1[l]*power[r-l]) % MOD + MOD) % MOD ;
        };

        function<int(int l, int r)> subhash2 = [&](int l, int r) -> int {
            return ((hash2[r] - hash2[l]*power[r-l]) % MOD + MOD) % MOD ;
        };
        
        vector<bool> res(n);
        for(int i = 0; i < n; i++) {
            int l = node[i].first;
            int r = node[i].second;
            int nl = n-l;
            int nr = n-r;
            if(subhash1(l, r) == subhash2(nr,nl)) {
                res[i] = 1;
            }
        }
        
        return res;
    }
};
