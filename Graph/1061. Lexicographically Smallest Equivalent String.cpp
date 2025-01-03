//  TC:O(n * ⍺(n)) SC:O(1)  ⍺(n)比lgn還要增長緩慢 時間複雜度更低
class Solution {
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        vector<int> parent(26);
        iota(parent.begin(), parent.end(), 0);
        auto find = [&](auto &&find, int x) -> int {
            if(x != parent[x]) parent[x] = find(find, parent[x]);
            return parent[x];
        };
        auto union_ = [&](int x, int y) -> void {
            x = find(find, x), y = find(find, y);
            if(x < y) {
                parent[y] = x;
            } else {
                parent[x] = y;
            }
        };

        for(int i = 0; i < s1.size(); i++) {
            if(find(find, s1[i] - 'a') != find(find, s2[i] - 'a')) {
                union_(s1[i] - 'a', s2[i] - 'a');
            }
        }

        string res = baseStr;
        for(int i = 0; i < baseStr.size(); i++) {
            int pa = find(find, baseStr[i]-'a');
            res[i] = pa + 'a';
        }
        return res;
    }
};
