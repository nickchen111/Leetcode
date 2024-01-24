/*
252. Meeting Rooms I
描述
给定一系列的会议时间间隔，包括起始和结束时间[[s1,e1]，[s2,e2]，…(si < ei)，确定一个人是否可以参加所有会议。
输入: intervals = [(0,30),(5,10),(15,20)]
输出: false
解释:
(0,30), (5,10) 和 (0,30),(15,20) 这两对会议会冲突
样例2

输入: intervals = [(5,8),(9,15)]
输出: true
解释:
这两个时间段不会冲突

*/

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

//TC:O(nlgn) SC:O(n)
class Solution {
public:
    bool canAttendMeetings(vector<Interval>& intervals) 
    {
        vector<pair<int,int>>q;
        for (int i=0; i<intervals.size(); i++)
        {
            q.push_back({intervals[i].start,1});
            q.push_back({intervals[i].end,-1});
        }
        
        sort(q.begin(),q.end());
        
        int count = 0;
        for (int i=0; i<q.size(); i++)
        {
            count+=q[i].second;
            if (count>1) return false;
        }
        return true;
            
    }
};

//map TC:O(nlgn) SC:O(n)
class Solution {
public:
    bool canAttendMeetings(vector<Interval> &intervals) {
        map<int,int> map;
        for(int i = 0; i<intervals.size();i++){
            map[intervals[i].start]++;
            map[intervals[i].end]--;
        }

        int sum = 0;
        for(auto& [time:diff]:map){
            sum+=diff;
            if(sum > 1) return false;
        }
        return true;
    }
};
/*
判斷是否有重複的區間
用sweeping line輕鬆搞定
*/
