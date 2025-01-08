// 思路較好的寫法 TC:O(m + n * ⍺(m) + n * h + r)  h為每個集合的平均數量 m為請求次數 r為限制長度 SC:O(n* h)
class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        vector<int> pa(n);
        // vector<int> rank(n,1);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        // auto union_ = [&](int x, int y) -> void {
        //     x = find(x), y = find(y);
        //     if(x < y) pa[x] = y;
        //     else pa[y] = x;
        // };
        // 限制會是某個數字不能跟誰再一起 把它做 unordered_set 然後每次要做union前先判斷當下的union對象是否沒有包含我的地雷
        vector<unordered_map<int, bool>> hate(n);
        for(auto &r : restrictions) {
            hate[r[0]][r[1]] = true;
            hate[r[1]][r[0]] = true;
        }
        vector<bool> res(requests.size());
        for(int i = 0; i < requests.size(); i++) {
            int a = requests[i][0], b = requests[i][1];
            int rb = find(b);
            int ra = find(a);
            if(ra == rb) {
                res[i] = true;
                continue;
            }
            if(hate[ra].find(rb) != hate[ra].end()) {
                continue;
            }
            res[i] = true;
            if(hate[ra].size() > hate[rb].size()) swap(ra,rb); // 都讓較大集合承載
            for(auto &[v,_] : hate[ra]) {
                int x = find(v);
                hate[x][rb] = true;
                hate[rb][x] = true;
            }
            pa[ra] = rb;
        }
        return res;
    }
};

// 
class Solution {
public:
    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        vector<int> pa(n);
        // vector<int> rank(n+1,1);
        iota(pa.begin(), pa.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto union_ = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x < y) {
                pa[y] = x;
            }
            else pa[x] = y;
        };
        // 限制會是某個數字不能跟誰再一起 把它做 unordered_set 然後每次要做union前先判斷當下的union對象是否沒有包含我的地雷
        set<pair<int,int>> hate;
        for(auto &r : restrictions) {
            int mn = min(r[0], r[1]);
            int mx = max(r[0], r[1]);
            hate.insert({mn, mx});
        }
        vector<bool> res(requests.size());
        for(int i = 0; i < requests.size(); i++) {
            int a = requests[i][0], b = requests[i][1];
            int rb = find(b);
            int ra = find(a);
            if(ra == rb) {
                res[i] = true;
                continue;
            }
            bool flag = true;
            unordered_set<int> roota;
            unordered_set<int> rootb;
            for(int j = 0; j < n; j++) {
                if(find(j) == rb) rootb.insert(j);
            }
            for(int j = 0; j < n; j++) {
                if(find(j) == ra) roota.insert(j);
            }
            for(auto &rra : roota) {
                for(auto &rrb : rootb) {
                    int mn = min(rra, rrb);
                    int mx = max(rra, rrb);
                    if(hate.find({mn,mx}) != hate.end()) {
                        flag = false;
                        break;
                    }
                }
                if(flag==false) break;
            }
            if(flag) {
                union_(a, b);
                res[i] = true;
            }
        }
        return res;
    }
};
