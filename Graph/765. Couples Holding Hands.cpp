// UF TC: O(n * ⍺(n)) SC:O(n)
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        vector<int> parent(n / 2); // 每對情侶用一個 root 表示
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> find = [&](int x) -> int {
            if (x != parent[x]) parent[x] = find(parent[x]);
            return parent[x];
        };

        auto union_ = [&](int x, int y) {
            int rootX = find(x), rootY = find(y);
            if (rootX != rootY) {
                parent[rootX] = rootY;
            }
        };

        for (int i = 0; i < n; i += 2) {
            union_(row[i] / 2, row[i + 1] / 2);
        }

        // 計算連通塊的個數
        unordered_set<int> unique_roots;
        for (int i = 0; i < n / 2; ++i) {
            unique_roots.insert(find(i));
        }

        // 最小交換次數 = 總對數 - 連通塊數
        return n / 2 - unique_roots.size();
    }
};

// Greedy + Map
class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        unordered_map<int,int> correct;
        unordered_map<int,int> map;
        for(int i = 1; i < n; i+=2) {
            correct[i] = i-1;
            correct[i-1] = i;
            map[row[i]] = i;
            map[row[i-1]] = i-1;
        }
        int res = 0;
        for(int i = 1; i < n; i += 2) {
            if(correct[row[i]] != row[i-1]) {
                map[row[i-1]] = map[correct[row[i]]];
                swap(row[i-1], row[map[correct[row[i]]]]);
                res += 1;
            }
        }
        return res;
    }
};
