// Binary Search + UF TC:O(4 * mn * lgmn * ⍺(mn)) SC:O(mn)
class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        vector<int> pa(row*col+1);
        iota(pa.begin(), pa.end(), 0);
        unordered_set<int> arrive;
        for(int j = 0; j < col; j++) {
            arrive.insert(j);
        }
        auto find = [](int x, vector<int>& pa) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto union_ = [&](int x, int y, vector<int>& pa) -> void {
            x = find(x, pa), y = find(y, pa);
            if(x < y) pa[y] = x;
            else pa[x] = y;
        };
        
        auto check = [&](int mid) -> bool {
            vector<int> pa2 = pa;
            unordered_set<int> set;
            for(int i = 0; i < mid; i++) {
                set.insert((cells[i][0] - 1) * col + cells[i][1] - 1);
            }
            for(int i = 0; i < row; i++) {
                for(int j = 0; j < col; j++) {
                    if(set.find(i * col + j) != set.end()) continue;

                    if(i + 1 < row && set.find((i+1)*col+j) == set.end()) {
                        union_(i*col+j, (i+1)*col + j, pa2);
                    }
                    if(j + 1 < col && set.find(i*col+j+1) == set.end()) {
                        union_(i*col+j+1, i*col + j, pa2);
                    }
                    if(i-1 >= 0 && set.find((i-1)*col+j) == set.end()) {
                        union_(i*col+j, (i-1)*col + j, pa2);
                    }
                    if(j-1 >= 0 && set.find(i*col+j-1) == set.end()) {
                        union_(i*col+j-1, i*col + j, pa2);
                    }
                }
            }
            for(int j = 0; j < col; j++) {
                int cur = find((row-1)*col + j, pa2);
                if(arrive.find(cur) != arrive.end()) return true;
            }
            return false;
        };
        int left = 0, right = cells.size();
        while(left < right) {
            int mid = left + (right - left + 1) / 2;
            if(check(mid)) left = mid;
            else right = mid - 1;
        }

        return left;
    }
};

// 單純逆向traverse + UF TC:O(4 * mn * * ⍺(mn) + mn * n * ⍺(mn)) SC:O(mn)
class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        vector<int> pa(row*col+1);
        iota(pa.begin(), pa.end(), 0);
        unordered_set<int> arrive;
        for(int j = 0; j < col; j++) {
            arrive.insert(j);
        }
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto union_ = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x < y) pa[y] = x;
            else pa[x] = y;
        };
        unordered_set<int> set;
        for(int i = 0; i < cells.size(); i++) {
            set.insert((cells[i][0] - 1) * col + cells[i][1] - 1);
        }
        vector<int> dirs = {0,1,0,-1,0};
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                if(set.find(i * col + j) != set.end()) continue;
                for(int k = 1; k < dirs.size(); k++) {
                    int nx = i + dirs[k-1];
                    int ny = j + dirs[k];
                    if(nx >= 0 && ny >= 0 && nx < row && ny < col && set.find(nx*col + ny) == set.end()) union_(nx*col + ny, i * col + j);
                }
            }
        }
        for(int j = 0; j < col; j++) {
            int cur = find((row-1)*col + j);
            if(arrive.find(cur) != arrive.end()) return (int)cells.size();
        }
        
        for(int i = cells.size()-1; i >= 0; i--) {
            set.erase((cells[i][0]-1) * col + cells[i][1] - 1);
            for(int j = 1; j < dirs.size(); j++) {
                int nx = cells[i][0] - 1 + dirs[j-1];
                int ny = cells[i][1] - 1 + dirs[j];
                if(nx >= 0 && ny >= 0 && nx < row && ny < col && set.find(nx*col + ny) == set.end()) union_(nx*col + ny, (cells[i][0]-1) * col + cells[i][1] - 1);
            }
            for(int j = 0; j < col; j++) {
                int cur = find((row-1)*col + j);
                if(arrive.find(cur) != arrive.end()) return i;
            }
        }

        return 0;
        
    }
};


// 所以重點就是0row 是否跟n-1row 還是同一個聯通區塊
