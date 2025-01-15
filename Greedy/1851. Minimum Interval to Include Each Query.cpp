/*
1851. Minimum Interval to Include Each Query
*/

// 2025.01.15 Union Find TC:O(nlgn + n * ⍺(n)) SC:O(n)
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<pair<int,int>> query;
        for(int i = 0; i < queries.size(); i++) {
            query.push_back({queries[i], i});
        }
        sort(query.begin(), query.end());
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            return a[1] - a[0] < b[1] - b[0];
        });
        int m = queries.size();
        vector<int> pa(m+1);
        iota(pa.begin(), pa.end(), 0);
        vector<int> ans(m, -1);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        for (auto& p : intervals) {
           int l = p[0];
           int r = p[1];
           int length = r - l + 1;
           int i = lower_bound(query.begin(), query.end(), l, [](const auto& a, int b) {
               return a.first < b;
           }) - query.begin();
           for (i = find(i); i < m && query[i].first <= r; i = find(i + 1)) {
               ans[query[i].second] = length;
               pa[i] = i + 1;
           }
       }
        return ans;
    }
};

// sort+PQ + offline query TC:O(nlgn) SC:O(n)
class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        //sort + PQ with offline query
        vector<pair<int,int>> qs;//紀錄要改的index
        for(int i = 0; i<queries.size(); i++){
            qs.push_back({queries[i],i});
        }

        sort(intervals.begin(),intervals.end());
        sort(qs.begin(),qs.end());//qs排序從低到高 這樣在選的時候不合格的pop掉 被pop的對於後面的也不符合 不會影響後面的權益
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;//放 duration, right
        vector<int> res(queries.size(),-1);
        //先將所有left <= q的放進去pq裡面 pq裡面按照duration 排序 對應的值是他的right
        int i = 0;
        for(auto query:qs){
            auto [q,idx] = query;
            while(i < intervals.size() && intervals[i][0] <= q){
                pq.push({intervals[i][1]-intervals[i][0]+1,intervals[i][1]});
                i++;
            }
            while(!pq.empty() && pq.top().second < q){
                pq.pop();
            }
            if(!pq.empty()) res[idx] = pq.top().first;
        }

        return res;

    }
};
