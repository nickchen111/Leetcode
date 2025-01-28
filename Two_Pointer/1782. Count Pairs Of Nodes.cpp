// TC: O(nlogn+q(n+m))，其中 m 為 edges 的長度，q 為 queries 的長度。 SC:O(n + m)
class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        unordered_map<int, int> mp;
        vector<int> indegree(n);
        for(auto &e : edges) {
            int x = e[0]-1, y = e[1]-1;
            if(x > y) swap(x,y);
            indegree[x] += 1;
            indegree[y] += 1;
            mp[x << 16 | y] += 1;
        }
        vector<pair<int,int>>arr;
        for(int i = 0; i < n; i++) {
            arr.push_back({indegree[i], i});
        }
        ranges::sort(arr);
        int m = queries.size();
        vector<int> ans(m);
        for(int i = 0; i < m; i++) {
            int left = 0, right = n-1;
            while(left < right) {
                if(arr[left].first + arr[right].first <= queries[i]) {
                    left += 1;
                }
                else {
                    ans[i] += (right - left);
                    right -= 1;
                }
            }
            for(auto &[num, freq] : mp) {
                int a = (num >> 16);
                int b = (num & ((1 << 16) - 1));
                if(indegree[a] + indegree[b] > queries[i] && indegree[a] + indegree[b] - freq <= queries[i]) ans[i] -= 1;
            }
        }
        return ans;
    }
};
