// Sliding Window + Deque TC:O(n) SC:O(n)
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if(n == m) return n;
        arr.insert(arr.begin(), 0);
        vector<int> days(n+1);
        for(int i = 1; i <= n; i++) days[arr[i]] = i; // 某個點要翻他的天數
       
        deque<int> dq;
        int res = -1;
        // 維護長度為 m 的 每個格子 最晚多久會翻
        int i = 1;
        for(int j = 1; j <= n; j++) {
            // 入
            while(!dq.empty() && days[dq.back()] < days[j]) {
                dq.pop_back();
            }
            dq.push_back(j);
            // 出
            if(j - i + 1 == m) {
                if((days[dq.front()] < days[i-1] || i-1 == 0) && (j + 1 > n || days[dq.front()] < days[j+1])) {
                    res = max(res, min(i - 1 == 0 ? INT_MAX : days[i-1], j+1 > n ? INT_MAX : days[j+1]) - 1);
                }
                if(dq.front() == i) dq.pop_front();
                i++;
            }
        }

        return res;
        
    }
};

// Union Find TC:O(n * ⍺(n)) SC:O(n)
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if(n == m) return n;
        vector<int> pa(n+1);
        iota(pa.begin(), pa.end(), 0);
        vector<int> size(n+1,0);
        vector<int> visited(n+1);
        vector<int> groups(n+1);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto merge = [&](int x, int y) {
            x = find(x), y = find(y);
            if(x != y) {
                if(x < y) swap(x,y);
                pa[y] = x;
                groups[size[x]] -= 1;
                groups[size[y]] -= 1;
                size[x] += size[y];
                groups[size[x]] += 1;
            }
        };
        int ans = -1;
        for(int i = 0; i < n; i++) {
            size[arr[i]] += 1;
            groups[size[arr[i]]] += 1;
            if(visited[arr[i]-1] || arr[i]-1 == 0) {
                if(arr[i] - 1 > 0) {
                    merge(arr[i]-1, arr[i]);
                }
            }
            if(arr[i] + 1 > n || visited[arr[i] + 1]) {
                if(arr[i] + 1 <= n) {
                    merge(arr[i]+1, arr[i]);
                }
            }
            visited[arr[i]] = true;
            if(groups[m]) ans = i + 1;
        }
        return ans;
    }
};

// Binary Search 反做 TC:O(nlgn) SC:O(n)
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        int n = arr.size();
        if(n == m) return n;
        map<int,int> map; // key 是起點
        unordered_map<int,int> len;
        map[1] = n;
        len[n] += 1;
        for(int i = n - 1; i >= 0; i--) {
            int pos = arr[i];
            auto iter = map.upper_bound(pos);
            iter = prev(iter);
            int curLen = iter->second - iter->first + 1;
            len[curLen] -= 1;
            if(curLen == 1) {
                map.erase(iter);
                if(m == curLen) return i;
                continue;
            }
            if(iter->first == pos) {
                int nxtLen = curLen - 1;
                int end = iter->second;
                map.erase(iter);
                map[pos+1] = end;
                if(nxtLen == m) return i;
                len[nxtLen] += 1;
            }
            else if(iter->second == pos) {
                int nxtLen = curLen - 1;
                int start = iter->first, end = iter->second - 1;
                map.erase(iter);
                map[start] = end;
                if(nxtLen == m) return i;
                len[nxtLen] += 1;
            }
            else {
                int nxtLen1 = pos - iter->first;
                int nxtLen2 = iter->second - pos;
                len[nxtLen1] += 1;
                len[nxtLen2] += 1;
                int start1 = iter->first, end1 = pos - 1, start2 = pos + 1, end2 = iter->second;
                map.erase(iter);
                map[start1] = end1;
                map[start2] = end2; 
                if(m == nxtLen2 || m == nxtLen1) return i;
            }
        }
        return -1;
    }
};

// 正做
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        // map<int, unordered_map<int,int>> map; 起點 -> 終點 長度?
        map<int, int> map; // 起點終點
        unordered_map<int,int> len;
        int n = arr.size();
        int res = 0;
        for(int i = 0; i < n; i++) {
            auto upper = map.upper_bound(arr[i]);
            auto lower = map.lower_bound(arr[i]);
            if(upper != map.end() && lower != map.begin()) {
                lower = prev(lower);
                // 兩段區間整體合併
                if(upper->first == arr[i] + 1 && lower->second + 1 == arr[i]) {
                    int prevLen = lower->second - lower->first + 1;
                    int afterLen = upper->second - upper->first + 1;
                    int start = lower->first;
                    int end = upper->second;
                    map.erase(lower);
                    map.erase(upper);
                    map[start] = end;
                    len[prevLen + afterLen + 1] += 1;
                    len[prevLen] -= 1;
                    len[afterLen] -= 1;
                }
                else if(upper->first == arr[i] + 1) {
                    int afterLen = upper->second - upper->first + 1;
                    int start = arr[i];
                    int end = upper->second;
                    map.erase(upper);
                    map[start] = end;
                    len[afterLen + 1] += 1;
                    len[afterLen] -= 1;
                }
                else if(lower->second + 1 == arr[i]) {
                    int prevLen = lower->second - lower->first + 1;
                    int start = lower->first;
                    int end = arr[i];
                    map.erase(lower);
                    map[start] = end;
                    len[prevLen + 1] += 1;
                    len[prevLen] -= 1;
                }
                else {
                    map[arr[i]] = arr[i];
                    len[1] += 1;
                }
            }
            else if(lower != map.begin()) {
                lower = prev(lower);
                if(lower->second + 1 == arr[i]) {
                    int prevLen = lower->second - lower->first + 1;
                    int start = lower->first;
                    int end = arr[i];
                    map.erase(lower);
                    map[start] = end;
                    len[prevLen + 1] += 1;
                    len[prevLen] -= 1;
                }
                else {
                    map[arr[i]] = arr[i];
                    len[1] += 1;
                }
            }
            else if(upper != map.end()) {
                if(upper->first == arr[i] + 1) {
                    int afterLen = upper->second - upper->first + 1;
                    int start = arr[i];
                    int end = upper->second;
                    map.erase(upper);
                    map[start] = end;
                    len[afterLen + 1] += 1;
                    len[afterLen] -= 1;
                }
                else {
                    map[arr[i]] = arr[i];
                    len[1] += 1;
                }
            }
            else {
                map[arr[i]] = arr[i];
                len[1] += 1;
            }

            if(len[m] > 0) {
                res = i + 1;
            }
        }

        return res == 0 ? -1 : res;

    }
};
