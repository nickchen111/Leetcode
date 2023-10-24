/*
57. Insert Interval
*/

// 對他做條件判斷 不需要sort  TC:O(n) SC:O(n)
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        //sort by starting point already
        if(intervals.empty()) return {newInterval};
        vector<vector<int>> res;
        
        // no overlap condition
        //在新區間之前所有區間
        int i = 0;
        while(i < intervals.size() && intervals[i][1] < newInterval[0]){
            res.push_back(intervals[i]);
            i++;
        }
        //overlap condition
        while(i < intervals.size() && !(intervals[i][0] > newInterval[1] || intervals[i][1] < newInterval[0])){
            newInterval[0] = min(newInterval[0],intervals[i][0]);
            newInterval[1] = max(intervals[i][1],newInterval[1]);
            i++;
        }
        res.push_back(newInterval);

        //在重疊區間後面所有區間 or 新的區間根本就在後面
        while(i < intervals.size()){
            res.push_back(intervals[i]);
            i++;
        }

        return res;
    }
};

// sweeping line TC:O(nlgn) SC:O(n)
class Solution {
    static bool cmp(pair<int,int>& a, pair<int,int>& b){
        if(a.first == b.first){
            return a.second > b.second;//代表+1的優先 -1結束在後
        }
        else return a.first < b.first;
        
    }
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> res;
        vector<pair<int,int>> q;//放入start & end point with score
        for(int i = 0; i<intervals.size(); i++){
            q.push_back({intervals[i][0],1});
            q.push_back({intervals[i][1],-1});
        }
        q.push_back({newInterval[0],1});
        q.push_back({newInterval[1],-1});
        sort(q.begin(),q.end(),cmp);

        int count = 0;
        int start = 0;
        int end = 0;
        for(int i = 0; i<q.size(); i++){
            count += q[i].second;
            if(count == 1 && q[i].second == 1){
                start = q[i].first;
            }
            else if(count == 0 && q[i].second == -1){
                end = q[i].first;
                res.push_back({start,end});
            }
        }

        return res;

    }
};

/*
一旦遇到重疊 找starting points最早的 以及 end 最晚的
*/
